#include<iostream>
#include "StudentID.h"

StudentID::StudentID()
{
    this->name="John Appleseed";
    this->sunet="jappleseed";
    this->idNumber=00000001;
}

StudentID::~StudentID()
{
    std::cout<<"Destructor is called"<<std::endl;
}

StudentID::StudentID(std::string name, std::string sunet, int idNumber) {
    this->name = name;
    this->sunet = sunet;
    if (idNumber >= 0) {
        this->idNumber = idNumber;
    } else {
        this->idNumber = 0;
    }
}

std::string StudentID::getName() {
    return name;
}

std::string StudentID::getSunet() {
    return sunet;
}

int StudentID::getIdNumber() {
    return idNumber;
}

void StudentID::setSunet(std::string sunet) {
    this->sunet = sunet; 
}

void StudentID::setIdNumber(int id) {
    this->idNumber = id; 
}

void StudentID::setName(std::string name) {
    this->name = name;
}