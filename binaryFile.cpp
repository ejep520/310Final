#include "binaryFile.h"
#include <vector>

using namespace std;

//-=-=-=-=- Public: import_employees -=-=-=-
/* Name: import_employees
* Last worked on by: Erik Jepsen <erik.jepsen@trojans.dsu.edu>
* Purpose: Move an array of employee records into a binary file.
* Arguments: 2
* EMP_REC[] records -- An array of records read in
* int linecount -- The number of records in records.
* Returns: NA
*/
void binaryFile::import_employees(EMP_REC records[], int linecount)
{
    record_count = linecount;
    out_data.open(filename, out_data.binary | out_data.trunc);
    if (out_data.rdstate() != out_data.goodbit)
    {
        throw new myException("Unable to open output file for writing.", ERROR);
    }
    for (int counter = 0; counter < record_count; counter++)
    {
        if (records[counter].dept >= dept_count)
        {
            dept_count = records[counter].dept + 1;
        }
        try
        {
            out_data.write((const char*)&records[counter], 40);
        }
        catch( myException &e)
        {
            cout << "Failed to write to binary file: ";
            cout << e.what() << endl;
        }
        
        
    }
    out_data.close();
}

/************************* PUBLIC: DESTRUCTOR************************/
binaryFile::~binaryFile()
{
    if (dept_headcount != nullptr)
    {
        delete [] dept_headcount;
        dept_headcount = nullptr;
    }
    if (departments != nullptr)
    {
        delete [] departments;
        departments = nullptr;
    }

}

void binaryFile::sort()
{
    int linecount = 0;
    in_data.open(filename, in_data.binary);
    if (in_data.rdstate() != in_data.goodbit)
    {
        throw new myException("Unable to open binary file for reading.", ERROR);
    }
    if (dept_headcount != nullptr)
    {
        delete [] dept_headcount;
        dept_headcount = nullptr;
    }
    dept_headcount = new int[dept_count];
    dept_headcount = {0};
    EMP_REC *Employees_in = new EMP_REC[record_count];
    for (int counter = 0; counter < record_count; counter++)
        in_data.read((char*)&Employees_in[counter], sizeof(EMP_REC));
    in_data.close();
    if (departments != nullptr)
    {
        delete [] departments;
        departments = nullptr;
    }
    departments = new bst[dept_count];
    for (int counter = 0; counter < record_count; counter++)
        {
            departments[Employees_in[counter].dept].insert(counter, Employees_in[counter].enumber);
        }
    // out_data.open(filename, out_data.binary|out_data.trunc);
    // for (int counter = 0; counter < dept_count; counter++)
    // {
        // ToDo: Write the binary file back out in dept/enumber order.
    // }
    // out_data.close();
    delete [] Employees_in;
}


//-=-=-=-=- Public: binaryFile::searchBinary -=-=-=-
/* Name: binaryFile::searchBinary
* Last worked on by: Erik Jepsen <erik.jepsen@trojans.dsu.edu>
* Purpose: Search for an employee by department and employee number
* Arguments: 2
* int dept -- Department number
* int emp_num -- Employee number
* Returns: bool
* True -- Employee was found with the provided search keys.
* False -- Employee was not found.
*/
bool binaryFile::searchBinary(int dept, int emp_num)
{
    bool return_value = false;
    if (departments == nullptr)
        return return_value;
    if (dept < 0)
        return return_value;
    if (dept >= dept_count)
        return return_value;
    return_value = departments[dept].search(emp_num) >= 0; // Awaiting a pull that mods bst.h and makes this correct.
    return return_value;
}

EMP_REC *binaryFile::retrieveEmployee(int dept, int emp_num)
{
    if (!searchBinary(dept, emp_num))
    {
        return nullptr;
    }
    EMP_REC *return_val = new EMP_REC;
    int offset = p_searchBinary(dept, emp_num);
    if (offset < 0)
        {
            cout<<"Offset = "<<offset<<endl;
            return return_val;
        }
    if (in_data.is_open())
        in_data.close();
    in_data.open(filename, in_data.binary);
    if (in_data.rdstate() != in_data.goodbit)
    {
        throw new myException("Unable to open binary file for reading.", ERROR);
    }
    in_data.seekg(offset*sizeof(EMP_REC), in_data.beg);
    in_data.read((char*)return_val, sizeof(EMP_REC));
    in_data.close();
    return return_val;
}

bool binaryFile::updateEmployee(EMP_REC new_rec)
{
    bool return_value = false;
    if (new_rec.dept < 0)
        return return_value;
    if (new_rec.dept > 4)
        return return_value;
    int offset = p_searchBinary(new_rec.dept, new_rec.enumber);
    if (offset < 0)
        return return_value;
    if (out_data.is_open())
        out_data.close();
    out_data.open(filename, out_data.binary);
    if (out_data.rdstate() != out_data.goodbit)
        throw new myException("Unable to open binary file for writing.", ERROR);
    out_data.seekp(offset*sizeof(EMP_REC), out_data.beg);
    out_data.write((char*)&new_rec, sizeof(EMP_REC));
    out_data.close();
    return_value = true;
    return return_value;
}

int binaryFile::p_searchBinary(int dept_no, int emp_no)
{
    int return_value = -1;
    int could_be = departments[dept_no].returnOffset(emp_no);
    if (could_be >= 0)
        return_value = could_be;
    return return_value;
}

//bstname.inOrder(&)