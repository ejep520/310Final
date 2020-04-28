#include <fstream>
#include <iostream>
#include "binaryFile.h"

using namespace std;

void bad_end(void);
string get_fn(int);

int main(int argc, char * argv[])
{
    ifstream in_data;
    string in_fn = "";
    string this_line = "";
    char temp_char = 0;
    int linecount = 0;
    int this_int = 0;
    switch (argc)
    {
        case 1:
            in_fn = get_fn(1);
            break;
        case 2:
            in_fn = get_fn(atoi(argv[1]));
            break;
        default:
            bad_end();
    }
    in_data.open(in_fn);
    if (in_data.rdstate() != 0)
    {
        cout<<"There was a problem opening "<<in_fn<<endl;
        return 1;
    }
    while (getline(in_data, this_line))
    {
        linecount++;
    }
    in_data.clear();
    in_data.seekg(0, in_data.beg);
    EMP_REC *Employees = new EMP_REC[linecount];
    for (this_int = 0; this_int < linecount; this_int++)
    {
        Employees[this_int] = EMP_REC();
        in_data >> Employees[this_int].dept;
        in_data >> temp_char;
        in_data >> Employees[this_int].enumber;
        in_data >> temp_char;
        in_data >> Employees[this_int].name;
    }
    in_data.close();
    binaryFile this_binary = binaryFile(Employees, linecount);
    this_binary.sort();
    delete [] Employees;
    return 0;
}

string get_fn(int this_file)
{
    const string small_fn = "smallOutput.txt";
    const string mid_fn = "mediumOutput.txt";
    const string big_fn = "largeOutput.txt";
    switch (this_file)
    {
        case 1:
            return small_fn;
        case 2:
            return mid_fn;
        case 3:
            return big_fn;
        default:
            bad_end();
    }
    return ""; // This should never happen.
}

void bad_end(void)
{
    cout << "Please choose an argument from the following list."<<endl;
    cout << "   excBinaryFile 1 -- for the file smallOutput.txt"<<endl;
    cout << "   excBinaryFile 2 -- for the file mediumOutput.txt"<<endl;
    cout << "   excBinaryFile 3 -- for the file largeOutput.txt"<<endl;
    exit(1);
}

/*
smallOutput.txt
================
0,45731,Leona 
1,37503,Briar 
2,58509,Kailey 
3,58510,Liv
4,44258,Anthony

0,18738,Hunter
1,63006,Annabel
2,757,Layton
3,68263,Maxim
4,65898,Rex

mediumOutput.txt
=================
0,243013,Amina 
1,135016,Dax
2,15013,Kaleb
3,105013,Violeta
4,297008,Huxley

0,139708,Benicio
1,250506,Amari
2,206998,Cory
3,6011,Zariyah
4,243119,Mariana

largeOutput.txt
================
0,205009,Isabelle
1,25013,Amiya
2,189715,Donald
3,155012,Virginia
4,430017,Magnolia

0,205508,Meadow
1,335014,Crosby
2,430013,Clara
3,5014,Watson
4,433415,Kyler
*/