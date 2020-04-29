#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__
#include <iostream>
#include <fstream>
#include "bst.h"
#include "bstNode.h"
#include "customErrorClass.h"


using namespace std;

typedef struct e_rec
{
    int dept = -1;
    int enumber = -1;
    char e_name[30] = "";
}EMP_REC;

class binaryFile{
    public:
    binaryFile() {};
    ~binaryFile(void);
    void import_employees(EMP_REC[], int); //import employee
    void sort(void); //sorting function
    bool searchBinary(int, int); //public method using employee number and department.
    EMP_REC *retrieveEmployee(int, int); //public method that returns employee name, number, and department. 
    void printEmployee(EMP_REC); //print name of employee from the retrieve employee function
    bool updateEmployee(EMP_REC); //update employee record
   
    private:
    //private fields
    ifstream in_data;
    ofstream out_data;
    const string filename = "output.bin";
    int record_count = 0;
    int dept_count = 0;
    int *dept_headcount = nullptr;
    bst *departments = nullptr;
    //private methods
    int p_searchBinary(int, int);//private method using employee number and department.
    int p_updateEmployee(EMP_REC); //private method to update employee information.
};

#endif
