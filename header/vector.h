#ifndef VECTOR_H
#define VECTOR_H
template <typename T> class Vector
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
    int get_size() {
        return size;
    }
    void clear() {
        if(arr) delete[] arr;
        arr = new T[1];
        capacity = 1;
        size = 0;
    }
};
#endif