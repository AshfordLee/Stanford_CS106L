#include<iostream>
#include "StudentID.h"


#define LIST_INITIALIZATION 0

StudentID::StudentID()
{
    name="John Appleseed";
    sunet="jappleseed";
    idNumber=00000001;
}

StudentID::~StudentID()
{
    std::cout<<"Destructor is called"<<std::endl;
}

#if LIST_INITIALIZATION
StudentID::StudentID(std::string name,std::string sunet,int idNumber)
{
    this->name=name;
    this->sunet=sunet;
    this->idNumber=idNumber;
}

#else

StudentID::StudentID(std::string name,std::string sunet,int idNumber)
{
    this->name=name;
    this->sunet=sunet;
    if (idNumber>=0)
    {
        this->idNumber=idNumber;
    }
    else {
    {
        this->idNumber=0;
    }
    }
}


std::string StudentID::get_name()
{
    return this->name;
}

std::string StudentID::get_sunet()
{
    return this->sunet;
}

int StudentID::get_idNumber()
{
    return this->idNumber;
}

void StudentID::setName(std::string name)
{
    this->name=name;
}

void StudentID::setSunet(std::string sunet)
{
    this->sunet=sunet;
}

void StudentID::setIdNumber(int id)
{
    this->idNumber=id;
}

#endif

