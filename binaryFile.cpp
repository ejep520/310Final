#include "binaryFile.h"

/************************* PUBLIC: CONSTRUCTOR*************************/
binaryFile::binaryFile()
{
    out_data.open(out_fn, out_data.binary | out_data.trunc);
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
    out_data.open(out_fn, out_data.binary | out_data.trunc);
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

}

void binaryFile::sort()
{
    int linecount = 0;
    in_data.open(out_fn, in_data.binary);
    if (in_data.rdstate() != in_data.goodbit)
    {
        throw new myException("Unable to open binary file for reading.", ERROR);
    }
    int dept_headcount[dept_count] = {0};
    EMP_REC *Employees_in = new EMP_REC[record_count];
    in_data.read((char*)&Employees_in, record_count*sizeof(EMP_REC));
    in_data.close();
    bst departments[dept_count];
    for (int counter = 0; counter < record_count; counter++)
    {
        if (!departments[Employees_in[counter].dept].insert_node(Employees_in[counter]))
        {
            throw new myException("Problem inserting a node into a bst.", ERROR);
        }
    }
    out_data.open(out_fn, out_data.binary|out_data.trunc);
    for (int counter = 0; counter < dept_count; counter++)
    {
        out_data.write((char*)departments[counter].bin_out_tree(), dept_headcount[counter]*sizeof(EMP_REC));
    }
    out_data.close();
    delete [] Employees_in;
}
