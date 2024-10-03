#pragma once

//--------------------
//---------------ARRAY
//--------------------
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

struct NodeFL
{
	std::string value;
	NodeFL* next;
};

struct ForwardList
{
private:

	NodeFL* head;
	NodeFL* tail;

public:

	ForwardList(std::string value);
	~ForwardList();
	bool isEmpty();
	int Size();
	void AddToEnd(std::string value);
	void AddToStart(std::string value);
	void DeleteLast();
	void DeleteFirst();
	void DeleteByValue(std::string value);
	NodeFL* Find(std::string value);
	void Print();
};

ForwardList::ForwardList(std::string value)
{
	NodeFL* startNode = new NodeFL{ value, nullptr };
	head = startNode;
	tail = startNode;
}

ForwardList::~ForwardList()
{
	NodeFL* currentNode = head;
	while (currentNode)
	{
		NodeFL* curNext = currentNode->next;
		delete currentNode;
		currentNode = curNext;
	}
	head = nullptr;
	tail = nullptr;
}

bool ForwardList::isEmpty()
{
	return head == nullptr;
}

int ForwardList::Size()
{
	if (isEmpty()) return -1;
	int sizeCounter = 0;
	NodeFL* currentNode = head;
	while (currentNode)
	{
		sizeCounter++;
		currentNode = currentNode->next;
	}

	return sizeCounter;
}

void ForwardList::AddToEnd(std::string value)
{
	NodeFL* newNode = new NodeFL{ value, nullptr };
	tail->next = newNode;
	tail = newNode;

}

void ForwardList::AddToStart(std::string value)
{
	NodeFL* newNode = new NodeFL{ value, head };
	head = newNode;
}

void ForwardList::DeleteLast()
{
	if (isEmpty()) return;
	if (Size() == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		NodeFL* current = head;
		while (current->next != tail)
		{
			current = current->next;
		}
		delete tail;
		tail = current;
		tail->next = nullptr;
	}
}

void ForwardList::DeleteFirst()
{
	if (isEmpty()) return;
	NodeFL* temp = head;
	head = head->next;
	delete temp;
}

void ForwardList::DeleteByValue(std::string value)
{
	if (isEmpty()) return;
	if (head->value == value)
	{
		NodeFL* temp = head;
		head = head->next;
		delete temp;

		if (head == nullptr)
			tail = nullptr;

		return;
	}

	NodeFL* prev = head;
	NodeFL* current = head->next;

	while (current != nullptr)
	{
		if (current->value == value)
		{
			prev->next = current->next;
			if (current == tail)
			{
				tail = prev;
			}
			delete current;
			return;
		}
		prev = current;
		current = current->next;
	}
}

NodeFL* ForwardList::Find(std::string value)
{
	NodeFL* current = head;
	while (current)
	{
		if (current->value == value)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr; // если значение не найдено
}

void ForwardList::Print()
{
	if (isEmpty()) std::cout << "Container is empty!" << std::endl;
	NodeFL* printNode = head;
	if (Size() == 1)
	{
		std::cout << head->value << std::endl;
	}
	else
	{
		while (printNode)
		{
			std::cout << printNode->value << " ";
			printNode = printNode->next;
		}
		std::cout << std::endl;
	}
}
