#pragma once

struct NodeQU
{
	std::string value;
	NodeQU* nextNode;
};

struct Queue
{
private:
	std::string value;
	NodeQU* head;
	NodeQU* tail;
public:

	Queue(std::string value)
	{
		NodeQU* startNode = new NodeQU{ value, nullptr };
		head = startNode;
		tail = startNode;
	}

	~Queue()
	{
		if (GetSize() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			NodeQU* currentNode = head;
			while (currentNode)
			{
				NodeQU* curNext = currentNode->nextNode;
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

	int GetSize()
	{
		NodeQU* currentNode = head;
		int size = 0;
		while (currentNode)
		{
			size++;
			currentNode = currentNode->nextNode;
		}
		return size;
	}

	void Enqueue(std::string value)
	{
		NodeQU* newNode = new NodeQU{ value, nullptr };
		tail->nextNode = newNode;
		tail = newNode;
	}

	void Dequeue()
	{
		if (isEmpty()) return;
		if (GetSize() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			NodeQU* newHead = head->nextNode;
			delete head;
			head = newHead;
		}

	}

	void Print()
	{
		NodeQU* currentNode = head;
		while (currentNode)
		{
			std::cout << currentNode->value << " ";
			currentNode = currentNode->nextNode;
		}
		std::cout << std::endl;
	}
};
