/**********|**********|**********|
Program: vector.h
Course: Object Oriented Programming And Data Structure
Trimester: 2430
Name: Chang Hoe Hin, Tee Kah Le, Loke Mun Chun, Ng Zai Kit
ID: 241UC2415N, 241UC2414Z, 241UC24160, 241UC240JT
Lecture Section: TC1L
Tutorial Section: TT4L
Email: chang.hoe.hin@student.mmu.edu.my, tee.kah.le@student.mmu.edu.my, loke.mun.chun@student.mmu.edu.my, ng.zai.kit@student.mmu.edu.my
Phone: 017-2453131, 011-2704 7627, 018-667 1883, 014-600 3652
**********|**********|**********/
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using namespace std;
template <typename T>
class Vector
{
private:
    T *arr;
    int capacity = 1;
    int size = 0;

public:
    Vector()
    {
        arr = new T[1];
    }
    ~Vector()
    {
        delete[] arr;
    }
    void push_back(T item)
    {
        if (capacity == size)
        {
            T *temp;
            capacity *= 2;
            temp = new T[capacity];
            for (int i = 0; i < (capacity / 2); i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        arr[size] = item;
        size += 1;
    }
    T operator[](int i)
    {
        if (i >= size)
        {
            std::cout << "ACCESS VIOLATION, OUT OF RANGE! CONSIDER ENDING THE PROGRAM" << std::endl;
            exit(-1);
        }
        return arr[i];
    }
    int get_size()
    {
        return size;
    }
    void clear()
    {
        if (arr)
            delete[] arr;
        arr = new T[1];
        capacity = 1;
        size = 0;
    }
};
#endif