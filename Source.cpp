#include <iostream>
using namespace std;

template<typename T> struct Array
{
private:

	T* arr;
	int currentSize;
	int memorySize;

public:

	Array ()
	{
		arr = new T[1];
		currentSize = 0;
		memorySize = 1;
	}

	~Array ()
	{
		delete[] arr;
	}

	void push_back (T data)
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

	void push_back (T data, int position)
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
		if (index < currentSize)
		{
			return arr[index];
		}
		else
		{
			throw "Wrong index!";
		}
		
	}

	void pop ()
	{
		currentSize--;
	}

	void del (int index)
	{
		if (index == currentSize - 1)
		{
			pop();
		}
		else
		{
			for (int i = index + 1; i < currentSize; i++)
			{
				push_back(arr[i], index);
			}
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
	Array<string> VECTORVECTOR;
	myVector.push_back("1");
	myVector.push_back("2");
	myVector.push_back("3");
	myVector.print();
	myVector.push_back("3",0);
	myVector.del(3);
	myVector.print();
	cout << myVector[0];

	


	return 0;
}