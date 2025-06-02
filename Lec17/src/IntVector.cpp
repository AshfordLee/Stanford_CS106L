#include "IntVector.h"
#include<stdexcept>

IntVector::IntVector()
{
    this->_size=0;
    this->_capacity=4;
    this->_data=new int[this->_capacity];
}

IntVector::~IntVector()
{
    delete[] this->_data;
}

void IntVector::resize()
{
    this->_capacity*=2;
    int* newVec=new int[this->_capacity];

    for(size_t i=0;i<this->_size;i++)
    {
        newVec[i]=this->_data[i];
    }

    delete[] this->_data;
    this->_data=newVec;
}

void IntVector::push_back(const int& value)
{
    if(this->_size==this->_capacity)
    {
        resize();
    }

    this->_data[this->_size]=value;
    this->_size++;
}

int& IntVector::at(size_t index)
{
    if(index<0 || index>=this->_size)
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
    return _data[index];
}

size_t IntVector::size()
{
  return _size;
}

bool IntVector::empty()
{
  return _size == 0;
}

IntVector::iterator IntVector::begin()
{
  return _data;
}

IntVector::iterator IntVector::end()
{
  return _data + _size;
}