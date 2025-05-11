#include<iostream>
#include "StudentID.h"
#include "IntVector.h"

void createStudentID()
{
    StudentID sid{"Jacob Roberts-Baca","jtrb",545};
    std::cout<<"Student ID: "<<sid.get_name()<<std::endl;
    std::cout<<"Sunet: "<<sid.get_sunet()<<std::endl;
    std::cout<<"ID Number: "<<sid.get_idNumber()<<std::endl;
}

int main()
{
    createStudentID();
    return 0;
}
    