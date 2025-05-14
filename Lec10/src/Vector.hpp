#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
public:
    using iterator = T*;

    Vector();
    ~Vector();

    void push_back(const T& value);

    T& at(size_t index);
    T& operator[](size_t index);

    size_t size();
    bool empty();

    iterator begin();
    iterator end();

private:
    size_t _size;
    size_t _capacity;
    T* _data;

    void resize();
};

// 实现部分
template <typename T>
Vector<T>::Vector()
{
    _size = 0;
    _capacity = 4;
    _data = new T[_capacity];
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] _data;   
}

template <typename T>
void Vector<T>::resize()
{
    auto newData = new T[_capacity*2];
    for(size_t i = 0; i < _size; i++)
    {
        newData[i] = _data[i];
    }

    delete[] _data;
    _capacity = _capacity*2;
    _data = newData;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (_size == _capacity)
    {
        resize();
    }

    _data[_size] = value;
    _size++;
}

template <typename T>
T& Vector<T>::at(size_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    return _data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    if (index >= _size)
    {
        throw std::out_of_range("Index out of range");
    }

    return _data[index];
}

template <typename T>
size_t Vector<T>::size()
{
    return _size;
}

template <typename T>
bool Vector<T>::empty()
{
    return _size == 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return _data;
}

template <typename T>   
typename Vector<T>::iterator Vector<T>::end()
{
    return _data + _size;
} 