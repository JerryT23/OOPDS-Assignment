#ifndef VECTOR_H
#define VECTOR_H
template <typename T> class Vector
{
private:
    T *arr;
    int size = 1;
    int element = 0;

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
        if (size == element)
        {
            T *temp;
            size *= 2;
            temp = new T[size];
            for (int i = 0; i < (size / 2); i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        arr[element] = item;
        element += 1;
    }
    T operator[](int i)
    {
        if (i >= element)
        {
            std::cout << "ACCESS VIOLATION, OUT OF RANGE! CONSIDER ENDING THE PROGRAM" << std::endl;
        }
        return arr[i];
    }
    int get_size() {
        return element;
    }
};
#endif