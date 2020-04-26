#include "binaryFile.h"

/************************* PUBLIC: CONSTRUCTOR*************************/
binaryFile::binaryFile()
{
    out_data.open(filename, out_data.binary | out_data.trunc);
    if (out_data.rdstate() != out_data.goodbit)
    {
        throw new myException("Unable to open output file for writing.", ERROR);
    }
    out_data.close();
}

//-=-=-=-=- Public: Constructor -=-=-=-
/* Name: Constructor
* Last worked on by: Erik Jepsen <erik.jepsen@trojans.dsu.edu>
* Purpose: Create an instance
* Arguments: 2
* EMP_REC[] records -- An array of records read in
* int linecount -- The number of records in records.
* Returns: NA
*/
binaryFile::binaryFile(EMP_REC records[], int linecount)
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
        out_data.write((const char*)&records[counter], sizeof(EMP_REC));
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
    in_data.read((char*)&Employees_in, record_count*sizeof(EMP_REC));
    in_data.close();
    if (departments != nullptr)
    {
        delete [] departments;
        departments = nullptr;
    }
    departments = new bst[dept_count];
    for (int counter = 0; counter < record_count; counter++)
    {
        if (!departments[Employees_in[counter].dept].insert(Employees_in[counter]))
        {
            throw new myException("Problem inserting a node into a bst.", ERROR);
        }
    }
    out_data.open(filename, out_data.binary|out_data.trunc);
    for (int counter = 0; counter < dept_count; counter++)
    {
        out_data.write((char*)departments[counter].bin_out_tree(), dept_headcount[counter]*sizeof(EMP_REC));
    }
    out_data.close();
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
    return_value = departments[dept].search(emp_num);
    return return_value;
}

EMP_REC *binaryFile::retrieveEmployee(int dept, int emp_num)
{
    if (!searchBinary(dept, emp_num))
    {
        return nullptr;
    }
    EMP_REC *return_val = p_retrieve_employee(dept, emp_num);
    return return_val;
}