#include "binaryFile.h"

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
    if (in_data.is_open())
        in_data.close();
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
    if (departments != nullptr)
    {
        delete [] departments;
        departments = nullptr;
    }
    departments = new bst[dept_count];
    EMP_REC Employee_in;
    for (int counter = 0; counter < record_count; counter++)
    {
        in_data.read((char*)&Employee_in, sizeof(EMP_REC));
        departments[Employee_in.dept].insert(counter, Employee_in.enumber);
    }
    in_data.close();
    vector<int> *new_order = new vector<int>[dept_count];
    for (int counter = 0; counter < dept_count; counter++)
        new_order[counter] = departments[counter].store();
    const string new_file = "newout.bin";
    ofstream new_out;
    EMP_REC *xfer_container = nullptr;
    new_out.open(new_file, new_out.binary | new_out.trunc);
    int get_emp_offset = 0;
    int inner_count = 0;
    bst *new_departments = new bst[dept_count];
    bst *old_departments = departments;
    if (new_out.rdstate() != new_out.goodbit)
    {
        perror("Unable to open output file.");
        throw new myException("Unable to open output file.", SYSTEM_FAILURE);
    }
    for (int counter = 0; counter < dept_count; counter++)
    {
        while (!new_order[counter].empty())
        {
            get_emp_offset = new_order[counter].front();
            new_order[counter].erase(new_order[counter].begin());
            xfer_container = retrieveEmployee(get_emp_offset);
            new_out.write((char*)xfer_container, sizeof(EMP_REC));
            new_departments[counter].insert(inner_count++, xfer_container->enumber);
            delete xfer_container;
        }
    }
    new_out.close();
    remove(filename.c_str());
    rename(new_file.c_str(), filename.c_str());
    departments = new_departments;
    // out_data.close();
    delete [] new_order;
    delete [] old_departments;
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
    int offset = p_searchBinary(dept, emp_num);
    return retrieveEmployee(offset);
}
EMP_REC *binaryFile::retrieveEmployee(int offset)
{
    EMP_REC *return_value = new EMP_REC;
    if (in_data.is_open())
        in_data.close();
    in_data.open(filename, in_data.binary);
    if (in_data.rdstate() != in_data.goodbit)
        throw new myException("Unable to open binary for reading.", SYSTEM_FAILURE);
    in_data.seekg(offset*sizeof(EMP_REC), in_data.beg);
    in_data.read((char*)return_value, sizeof(EMP_REC));
    in_data.close();
    return return_value;
}

bool binaryFile::updateEmployee(EMP_REC new_rec)
{
    bool return_value = false;
    EMP_REC *old_rec = nullptr;
    fstream update_stream;
    if (new_rec.dept < 0)
        return return_value;
    if (new_rec.dept >= dept_count)
        return return_value;
    int offset = p_searchBinary(new_rec.enumber);
    if (offset < 0)
        return return_value;
    old_rec = retrieveEmployee(offset);
    update_stream.open(filename, update_stream.binary|update_stream.in|update_stream.out);
    if (update_stream.rdstate() != update_stream.goodbit)
        throw new myException("Unable to open binary file for writing.", ERROR);
    update_stream.seekp(offset*sizeof(EMP_REC), out_data.beg);
    update_stream.write((char*)&new_rec, sizeof(EMP_REC));
    update_stream.close();
    sort();
    return_value = true;
    return return_value;
}

int binaryFile::p_searchBinary(int emp_no)
{
    int return_value = -1;
    for (int counter = 0; counter < dept_count; counter++)
    {
        return_value = departments[counter].returnOffset(emp_no);
        if (return_value >= 0)
            break;
    }
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
