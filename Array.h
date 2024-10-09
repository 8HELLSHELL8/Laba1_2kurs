#pragma once
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <type_traits>

template<typename T>
struct Array
{
private:
    T* arr;
    int currentSize;
    int memorySize;

public:

    Array()
    {
        static_assert(std::is_default_constructible<T>::value, "Type T must be default constructible");
        arr = new T[1];
        currentSize = 0;
        memorySize = 1;
    }

    Array(int size)
    {
        arr = new T[size];
        currentSize = 0;
        memorySize = size;
    }

    ~Array()
    {
        delete[] arr;
    }

    void push_back(T data)
    {
        if (currentSize == memorySize)
        {
            T* tempArr = new T[memorySize * 2];
            for (int i = 0; i < currentSize; i++)
            {
                tempArr[i] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
            memorySize = memorySize * 2;
        }
        arr[currentSize] = data;
        currentSize++;
    }

    void push_back(T data, int position)
    {
        if (position == currentSize)
        {
            push_back(data);
        }
        else {
            arr[position] = data;
        }
    }

    T& operator[] (int index)
    {
        if (index < 0 || index >= currentSize)
        {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    int getSize()
    {
        return currentSize;
    }

    void pop()
    {
        if (currentSize == 0) return;
        currentSize--; // Уменьшаем только размер массива
    }

    void pop(int index)
    {
        if (index < 0 || index >= currentSize)
        {
            std::cerr << "Index out of range!" << std::endl;
            return;
        }
        if (index == (currentSize - 1))
        {
            pop();
        }
        else
        {
            T* temp = new T[currentSize - 1];
            for (int i = 0, j = 0; i < currentSize; i++)
            {
                if (i != index)
                {
                    temp[j++] = arr[i];
                }
            }
            delete[] arr;
            arr = temp;
            currentSize--;
        }
    }

    void get(T value)
    {
        if (currentSize == 0)
        {
            std::cout << "Empty container!" << std::endl;
            return;
        }
        for (int i = 0; i < currentSize; i++)
        {
            if (arr[i] == value)
            {
                std::cout << "Index in array is: " << arr[i] << std::endl;
                return;
            }
        }
        std::cout << "Element is not in array!" << std::endl;
        return;
    }

    void print()
    {
        if (currentSize == 0)
        {
            std::cout << "Empty container!" << std::endl;
            return;
        }
        for (int i = 0; i < currentSize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void printInFile(std::fstream& file)
    {
        if (currentSize == 0)
        {
            file << "Empty container!" << std::endl;
            return;
        }
        for (int i = 0; i < currentSize; i++)
        {
            file << arr[i] << " ";
        }
        file << std::endl;
    }
};


