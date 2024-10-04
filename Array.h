#pragma once

template<typename T>
struct Array
{
private:
	T* arr;
	int currentSize;
	int memorySize;

public:
	Array();
	~Array();
	void push_back(T data);
	void push_back(T data, int position);
	T& operator[] (int index);
	int getSize();
	void pop();
	void del(int index);
	void print();
};

template<typename T>
Array<T>::Array()
{
	arr = new T[1];
	currentSize = 0;
	memorySize = 1;
}

template<typename T>
Array<T>::~Array()
{
	delete[] arr;
}

template<typename T>
void Array<T>::push_back(T data)
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

template<typename T>
void Array<T>::push_back(T data, int position)
{
	if (position == currentSize)
	{
		push_back(data);
	}
	else {
		arr[position] = data;
	}
}

template<typename T>
T& Array<T>::operator[] (int index)
{
	if (index < 0 || index >= currentSize)
	{
		static T emptyValue;
		std::cerr << "Index out of range! Returned an empty value";
		return emptyValue;
	}
	return arr[index];
}

template<typename T>
int Array<T>::getSize()
{
	return currentSize;
}

template<typename T>
void Array<T>::pop()
{
	if (getSize() == 0) return;
	T* temp = new T[memorySize - 1];
	for (int i = 0; i < currentSize - 1; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	memorySize--;
	currentSize--;
}

template<typename T>
void Array<T>::del(int index)
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
		for (int i = 0, j = 0; i < currentSize; i++, j++)
		{
			if (i != index)
			{
				temp[j] = arr[i];
			}
			else
			{
				j = i - 1;
				continue;
			}
		}
		delete[] arr;
		arr = temp;
		currentSize--;
		memorySize--;
	}
}

template<typename T>
void Array<T>::print()
{
	for (int i = 0; i < currentSize; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

//--------------------
//---------------FLIST
//--------------------

