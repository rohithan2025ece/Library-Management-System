#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;
class student
{
    private:
    public:
       void menu();
};
void student::menu()
{
    int choice;
    char x;
    system("cls");

    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"\t\t\t| STUDENT MANAGEMENT SYSTEM |"<<endl;
    cout<<"\t\t\t----------------------------"<<endl;
    cout<<"\t\t\t 1. Enter New Record"<<endl;
    cout<<"\t\t\t 2. Display Record"<<endl;
    cout<<"\t\t\t 3. Modify Record"<<endl;
    cout<<"\t\t\t 4. Search Record"<<endl;
    cout<<"\t\t\t 5. Delete Record"<<endl;
    cout<<"\t\t\t 6.Exit"<<endl;

}
main()
{
    student project;
    project.menu();
    return 0;
}
