#pragma once

#include <fstream>
#include <iostream>

template<typename T>
struct NodeQU
{
	T value;
	NodeQU<T>* nextNode;
};

template<typename T>
struct Queue
{
private:
	NodeQU<T>* head;
	NodeQU<T>* tail;
public:
	Queue() : head(nullptr), tail(nullptr) {}

	~Queue()
	{
		NodeQU<T>* currentNode = head;
		while (currentNode)
		{
			NodeQU<T>* curNext = currentNode->nextNode;
			delete currentNode;
			currentNode = curNext;
		}
		head = nullptr;
		tail = nullptr;
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	int GetSize()
	{
		NodeQU<T>* currentNode = head;
		int size = 0;
		while (currentNode)
		{
			size++;
			currentNode = currentNode->nextNode;
		}
		return size;
	}

	void Enqueue(T value)
	{
		NodeQU<T>* newNode = new NodeQU<T>{ value, nullptr };
		if (isEmpty())
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->nextNode = newNode;
			tail = newNode;
		}
	}

	void Dequeue()
	{
		if (isEmpty()) return;

		NodeQU<T>* newHead = head->nextNode;
		delete head;
		head = newHead;

		if (!head)
		{
			tail = nullptr;
		}
	}

	T Front()
	{
		if (!isEmpty())
		{
			return head->value;
		}
		throw std::runtime_error("Queue is empty!");
	}

	void Print()
	{
		NodeQU<T>* currentNode = head;
		while (currentNode)
		{
			std::cout << currentNode->value << " ";
			currentNode = currentNode->nextNode;
		}
		std::cout << std::endl;
	}

	T& operator[](int index)
	{
		if (index < 0 || index >= GetSize())
		{
			throw std::out_of_range("Index is out of range!");
		}

		NodeQU<T>* currentNode = head;
		int currentIndex = 0;

		while (currentNode)
		{
			if (currentIndex == index)
			{
				return currentNode->value;
			}
			currentNode = currentNode->nextNode;
			currentIndex++;
		}

		throw std::out_of_range("Index is out of range!"); // На случай ошибки
	}

	T operator[](int index) const
	{
		if (index < 0 || index >= GetSize())
		{
			throw std::out_of_range("Index is out of range!");
		}

		NodeQU<T>* currentNode = head;
		int currentIndex = 0;

		while (currentNode)
		{
			if (currentIndex == index)
			{
				return currentNode->value;
			}
			currentNode = currentNode->nextNode;
			currentIndex++;
		}

		throw std::out_of_range("Index is out of range!"); // На случай ошибки
	}

	void PrintInFile(std::fstream& file)
	{
		NodeQU<T>* currentNode = head;
		while (currentNode)
		{
			file << currentNode->value << " ";
			currentNode = currentNode->nextNode;
		}
		file << std::endl;
	}

};
