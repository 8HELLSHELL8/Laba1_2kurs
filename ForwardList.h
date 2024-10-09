#pragma once
#include <fstream>
#include <iostream>

template<typename T>
struct NodeFL
{
	T value;
	NodeFL* next;
};

template<typename T>
struct ForwardList
{
private:

	NodeFL<T>* head;
	NodeFL<T>* tail;

public:

	ForwardList(T value)
	{
		NodeFL<T>* startNode = new NodeFL<T>{ value, nullptr };
		head = startNode;
		tail = startNode;
	}

	~ForwardList()
	{
		if (Size() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			NodeFL<T>* currentNode = head;
			while (currentNode)
			{
				NodeFL<T>* curNext = currentNode->next;
				delete currentNode;
				currentNode = curNext;
			}
			head = nullptr;
			tail = nullptr;
		}
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	int Size()
	{
		if (isEmpty()) return -1;
		int sizeCounter = 0;
		NodeFL<T>* currentNode = head;
		while (currentNode)
		{
			sizeCounter++;
			currentNode = currentNode->next;
		}

		return sizeCounter;
	}

	void push_back(T value)
	{
		NodeFL<T>* newNode = new NodeFL<T>{ value, nullptr };
		tail->next = newNode;
		tail = newNode;
	}

	void push_back(T value, int index)
	{
		if (index == 0) AddToStart(value);
		else if (index == Size() - 1) push_back(value);
	}

	void AddToStart(T value)
	{
		NodeFL<T>* newNode = new NodeFL<T>{ value, head };
		head = newNode;
	}

	void DeleteLast()
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
			NodeFL<T>* current = head;
			while (current->next != tail)
			{
				current = current->next;
			}
			delete tail;
			tail = current;
			tail->next = nullptr;
		}
	}

	void DeleteFirst()
	{
		if (isEmpty()) return;
		if (Size() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		NodeFL<T>* temp = head;
		head = head->next;
		delete temp;
	}

	void DeleteByValue(T value)
	{
		if (isEmpty()) return;
		if (head->value == value)
		{
			NodeFL<T>* temp = head;
			head = head->next;
			delete temp;

			if (head == nullptr)
				tail = nullptr;

			return;
		}

		NodeFL<T>* prev = head;
		NodeFL<T>* current = head->next;

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

	void Pop()
	{
		DeleteLast();
	}

	void Pop(int index)
	{
		if (index == Size() - 1) DeleteLast();
		else if (index == 0) DeleteFirst();

	}

	NodeFL<T>* Find(T value)
	{
		NodeFL<T>* current = head;
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

	void Print()
	{
		if (isEmpty()) std::cout << "Container is empty!" << std::endl;
		NodeFL<T>* printNode = head;
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

	void PrintInFile(std::fstream& file)
	{
		if (isEmpty()) file << "Container is empty!" << std::endl;
		NodeFL<T>* printNode = head;
		if (Size() == 1)
		{
			file << head->value << std::endl;
		}
		else
		{
			while (printNode)
			{
				file << printNode->value << " ";
				printNode = printNode->next;
			}
			file << std::endl;
		}
	}
};

















