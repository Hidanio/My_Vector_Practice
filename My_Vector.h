#ifndef MY_VECTOR_PRACTICE_MY_VECTOR_H
#define MY_VECTOR_PRACTICE_MY_VECTOR_H
#include <cstdio>

template<class T> class My_Vector
{
    size_t	_size;
    T*		_elements;
    size_t	_space;

public:
My_Vector()= default;
void push_back(const T& value);
};










#endif //MY_VECTOR_PRACTICE_MY_VECTOR_H
