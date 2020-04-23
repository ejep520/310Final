#ifndef __BINARY_FILE__H__
#define __BINARY_FILE__H__

using namespace std;

class binaryFile {
    public:
    //public fields

    //public methods
    binaryFile();
    ~binaryFile();
    sort(); //placeholder for sorting function
    bool searchBinary(int, int); //public method using employee number and department.
    structname retrieveEmployee(int, int); //public method that returns employee name, number, and department. still needs the struct as a return
    void printEmployee(structname); //placeholder for printing name of employee from the retrieve employee function
    bool updateEmployee(structname);
   
    private:
    //private fields

    //public methods
    p_searchBinary(int, int);//private method using employee number and department. Still needs a return (offset within the file)
    void p_updateEmployee(structname); //private method to update employee information. Takes a struct to update info.
};

#endif