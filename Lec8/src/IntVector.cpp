#include "IntVector.h"
#include<stdexcept>

IntVector::IntVector()
{
    this->_size=0;
    this->_capacity=0;
    this->_data=new int[_capacity];
}

IntVector::~IntVector()
{
    delete[] _data;
}

void IntVector::resize()
{
    this->_capacity=this->_capacity*2;
    int* newVec=new int[_capacity];
    for(int i=0;i<this->_size;i++)
    {
        newVec[i]=_data[i];
    }

    delete[] this->_data;
    this->_data=newVec;
}

void IntVector::push_back(const int& value)
{
    if (this->_size==this->_capacity)
    {
        this->resize();
    }

    this->_data[this->_size]=value;
    this->_size++;
}

int& IntVector::at(size_t index)
{
    if (index<0 || index>=this->_size || index>=this->_capacity)
    {
        throw std::out_of_range("Index out of range");
    }

    else
    {
        return this->_data[index];
    }
}

int& IntVector::operator[](size_t index)
{
    return this->at(index);
}

size_t IntVector::size()
{
    return this->_size;
}

bool IntVector::empty()
{
    if (this->_size==0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

IntVector::iterator IntVector::begin()
{
    return this->_data;
}

IntVector::iterator IntVector::end()
{
    return this->_data+this->_size;
}