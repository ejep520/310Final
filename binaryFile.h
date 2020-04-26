#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__
#include <iostream>
#include <fstream>
#include "bst.h"
#include "customErrorClass.h"


using namespace std;

typedef struct e_rec
{
    int dept;
    int enumber;
    char name[30];
}EMP_REC;

class binaryFile {
    public:
    //public fields

    //public methods
    binaryFile();
    binaryFile(EMP_REC*, int);
    ~binaryFile();
    void sort(); //placeholder for sorting function
    bool searchBinary(int, int); //public method using employee number and department.
    EMP_REC *retrieveEmployee(int, int); //public method that returns employee name, number, and department. still needs the struct as a return
    void printEmployee(EMP_REC); //placeholder for printing name of employee from the retrieve employee function
    bool updateEmployee(EMP_REC);
   
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
    int p_searchBinary(int, int);//private method using employee number and department. Still needs a return (offset within the file)
    void p_updateEmployee(EMP_REC); //private method to update employee information. Takes a struct to update info.
};

#endif
