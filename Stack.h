#pragma once

#include <iostream>
#include <fstream>

template<typename T>
struct Stack
{
private:

	T* array;
	int currentSize;
	int memoryCapacity;

public:

	Stack()
	{
		array = new T[1];
		currentSize = 0;
		memoryCapacity = 1;
	}

	~Stack()
	{
		delete[] array;
	}

	void Push_back(T value)
	{
		if (currentSize == memoryCapacity)
		{
			T* tempArr = new T[memoryCapacity * 2];
			for (int i = 0; i < currentSize; i++)
			{
				tempArr[i] = array[i];
			}
			delete[] array;
			array = tempArr;
			memoryCapacity = memoryCapacity * 2;
		}
		array[currentSize] = value;
		currentSize++;
	}

	bool isEmpty()
	{
		return currentSize == 0;
	}

	void Pop()
	{
		if (isEmpty()) return;
		T* temp = new T[memoryCapacity - 1];
		for (int i = 0; i < currentSize - 1; i++)
		{
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
		memoryCapacity--;
		currentSize--;
	}

	void Print()
	{
		if (isEmpty())
		{
			std::cout << "Empty container!" << std::endl;
			return;
		}

		for (int i = 0; i < currentSize; i++)
		{
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

	void PrintInFile(std::fstream& file)
	{
		if (isEmpty())
		{
			file << "Empty container!" << std::endl;
			return;
		}

		for (int i = 0; i < currentSize; i++)
		{
			file << array[i] << " ";
		}
		file << std::endl;
	}

	T& operator[] (int index)
	{
		if (index < 0 || index >= currentSize)
		{
			static T emptyValue;
			std::cerr << "Index out of range! Returned an empty value";
			return emptyValue;
		}
		return array[index];
	}

};
