#include <iostream>
using namespace std;

template<typename T> struct Array
{
private:

	T* arr;
	int currentSize;
	int memorySize;

public:

	Array()
	{
		arr = new T[1];
		currentSize = 0;
		memorySize = 1;
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
			static T emptyValue;
			cerr << "Index out of range! Returned an empty value";
			return emptyValue;
		}
		return arr[index];
	}

	int getSize()
	{
		return currentSize;
	}

	void pop()
	{
		currentSize--;
	}

	void del(int index)
	{
		if (index < 0 || index >= currentSize)
		{
			
			cerr << "Index out of range!" << endl;
			return;
		}
		if (index == (currentSize - 1))
		{
			pop();
		}
		else
		{
			T* temp = new T[currentSize - 1];
			for (int i = 0,j = 0; i < currentSize; i++, j++)
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

	void print()
	{
		for (int i = 0; i < currentSize; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}


};

int main()
{
	Array<string> myVector;
	

	


	return 0;
}