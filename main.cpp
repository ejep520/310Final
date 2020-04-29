#include <cstring>
#include <fstream>
#include <iostream>
#include "binaryFile.h"

using namespace std;

void bad_end(void);
string get_fn(int);
EMP_REC *get_test_data(int);

int main(int argc, char * argv[])
{
    ifstream in_data;
    string in_fn = "";
    string this_line = "";
    char temp_char = 0;
    int linecount = 0;
    int counter = 0;
    int file_num = 1;
    switch (argc)
    {
        case 1:
            in_fn = get_fn(file_num);
            break;
        case 2:
            file_num = atoi(argv[1]);
            in_fn = get_fn(file_num);
            break;
        default:
            bad_end();
    }
    in_data.open(in_fn);
    if (in_data.rdstate() != 0)
    {
        throw new myException("Problem opening file", SYSTEM_FAILURE);
    }
    while (getline(in_data, this_line))
    {
        linecount++;
    }
    in_data.clear();
    in_data.seekg(0, in_data.beg);
    EMP_REC *Employees = new EMP_REC[linecount];
    for (counter = 0; counter < linecount; counter++)
    {
        Employees[counter] = EMP_REC();
        in_data >> Employees[counter].dept;
        in_data >> temp_char;
        in_data >> Employees[counter].enumber;
        in_data >> temp_char;

        try
        {
            in_data >> Employees[counter].e_name;
        }
        catch( logic_error &e)
        {
            cout << "Employee name exceeds 30 characters: ";
            cout << e.what() << endl;
        }
        
        
    }
    in_data.close();
    binaryFile this_binary;
    this_binary.import_employees(Employees, linecount);
    delete [] Employees;
    this_binary.sort();
    EMP_REC *test_data = get_test_data(file_num);
    EMP_REC *real_data = nullptr;
    for (counter = 0; counter < 10; counter++)
    {
        real_data = this_binary.retrieveEmployee(test_data[counter].dept, test_data[counter].enumber);
        if ((counter > 4) ^ (strcmp(real_data->e_name, test_data[counter].e_name)== 0))
        {
            cout<<"Test "<<counter+1<<" of 10 passed."<<endl;
            cout<<"Results..."<<endl;
            cout<<"Department "<<real_data->dept<<" == "<<test_data[counter].dept<<endl;
            cout<<"Number "<<real_data->enumber<<" == "<<test_data[counter].enumber<<endl;
            cout<<"Name "<<real_data->e_name<<" == "<<test_data[counter].e_name<<endl;
        }
        else
        {
            cout<<"Test "<<counter+1<<" of 10 failed."<<endl;
            cout<<"Results..."<<endl;
            cout<<"Department "<<real_data->dept<<" == "<<test_data[counter].dept<<endl;
            cout<<"Number "<<real_data->enumber<<" == "<<test_data[counter].enumber<<endl;
            cout<<"Name "<<real_data->e_name<<" != "<<test_data[counter].e_name<<endl;
        }
    }
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

EMP_REC *get_test_data(int file_num)
{
    if ((file_num < 1) || (file_num > 3))
        bad_end();
    EMP_REC *return_value = new EMP_REC[10];
    const size_t name_size = sizeof(EMP_REC::e_name);
    switch(file_num)
    {
        case 1:
            return_value[0].dept = 0;
            return_value[0].enumber = 45731;
            strncpy(return_value[0].e_name, "Leona", name_size);
            return_value[1].dept = 1;
            return_value[1].enumber = 37503;
            strncpy(return_value[1].e_name, "Briar", name_size);
            return_value[2].dept = 2;
            return_value[2].enumber = 58509;
            strncpy(return_value[2].e_name, "Kailey", name_size);
            return_value[3].dept =3;
            return_value[3].enumber = 58510;
            strncpy(return_value[3].e_name, "Liv", name_size);
            return_value[4].dept = 4;
            return_value[4].enumber = 44258;
            strncpy(return_value[4].e_name, "Anthony", name_size);
            return_value[5].dept = 0;
            return_value[5].enumber = 18738;
            strncpy(return_value[5].e_name, "Hunter", name_size);
            return_value[6].dept = 1;
            return_value[6].enumber = 63006;
            strncpy(return_value[6].e_name, "Annabel", name_size);
            return_value[7].dept = 2;
            return_value[7].enumber = 757;
            strncpy(return_value[7].e_name, "Layton", name_size);
            return_value[8].dept = 3;
            return_value[8].enumber = 68263;
            strncpy(return_value[8].e_name, "Maxim", name_size);
            return_value[9].dept = 4;
            return_value[9].enumber = 65898;
            strncpy(return_value[9].e_name, "Rex", name_size);
            break;
        case 2:
            return_value[0].dept = 0;
            return_value[0].enumber = 243013;
            strncpy(return_value[0].e_name, "Amina", name_size);
            return_value[1].dept = 1;
            return_value[1].enumber = 135016;
            strncpy(return_value[1].e_name, "Dax", name_size);
            return_value[2].dept = 2;
            return_value[2].enumber = 15013;
            strncpy(return_value[2].e_name, "Kaleb", name_size);
            return_value[3].dept = 3;
            return_value[3].enumber = 105013;
            strncpy(return_value[3].e_name, "Violeta", name_size);
            return_value[4].dept = 4;
            return_value[4].enumber = 297008;
            strncpy(return_value[4].e_name, "Huxley", name_size);
            return_value[5].dept = 0;
            return_value[5].enumber = 139708;
            strncpy(return_value[5].e_name, "Benicio", name_size);
            return_value[6].dept = 1;
            return_value[6].enumber = 250506;
            strncpy(return_value[6].e_name, "Amari", name_size);
            return_value[7].dept = 2;
            return_value[7].enumber = 206998;
            strncpy(return_value[7].e_name, "Cory", 30);
            return_value[8].dept = 3;
            return_value[8].enumber = 6011;
            strncpy(return_value[8].e_name, "Zariyah", 30);
            return_value[9].dept = 4;
            return_value[9].enumber = 243119,
            strncpy(return_value[9].e_name, "Mariana", 30);
            break;
        default:
            return_value[0].dept = 0;
            return_value[0].enumber = 205009;
            strncpy(return_value[0].e_name, "Isabelle", 30);
            return_value[1].dept = 1;
            return_value[1].enumber = 25013;
            strncpy(return_value[1].e_name, "Amiya", 30);
            return_value[2].dept = 2;
            return_value[2].enumber = 189715;
            strncpy(return_value[2].e_name, "Donald", 30);
            return_value[3].dept = 3;
            return_value[3].enumber = 155012;
            strncpy(return_value[3].e_name, "Virginia", 30);
            return_value[4].dept = 4;
            return_value[4].enumber = 430017;
            strncpy(return_value[4].e_name, "Magnolia", 30);
            return_value[5].dept = 0;
            return_value[5].enumber = 205508,
            strncpy(return_value[5].e_name, "Meadow", 30);
            return_value[6].dept = 1;
            return_value[6].enumber = 335014,
            strncpy(return_value[6].e_name, "Crosby", 30);
            return_value[7].dept = 2;
            return_value[7].enumber = 430013,
            strncpy(return_value[7].e_name, "Clara", 30);
            return_value[8].dept = 3;
            return_value[8].enumber = 5014;
            strncpy(return_value[8].e_name, "Watson", 30);
            return_value[9].dept = 4;
            return_value[9].enumber = 433415;
            strncpy(return_value[9].e_name, "Kyler", 30);
    }
    return return_value;
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