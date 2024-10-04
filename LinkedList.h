#pragma once

struct NodeLL
{
	std::string value;
	NodeLL* previousNode;
	NodeLL* nextNode;
};

struct LinkedList
{
private:
	NodeLL* tail;
	NodeLL* head;
public:

	LinkedList(std::string value)
	{
		NodeLL* startNode = new NodeLL{ value, nullptr, nullptr };
		head = startNode;
		tail = startNode;
	}

	~LinkedList()
	{
		if (GetSize() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			NodeLL* currentNode = head;
			while (currentNode)
			{
				NodeLL* curNext = currentNode->nextNode;
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
		NodeLL* currentNode = head;
		int size = 0;
		while (currentNode)
		{
			size++;
			currentNode = currentNode->nextNode;
		}
		return size;
	}

	void AddToEnd(std::string value)
	{

		NodeLL* newNode = new NodeLL{ value, tail, nullptr };
		tail->nextNode = newNode;
		tail = newNode;
	}

	void AddToStart(std::string value)
	{
		NodeLL* newNode = new NodeLL{ value, nullptr, head };
		head->previousNode = newNode;
		head = newNode;
	}

	void DeleteLast()
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
			NodeLL* prevNode = tail->previousNode;
			prevNode->nextNode = nullptr;
			delete tail;
			tail = prevNode;
		}
	}

	void DeleteFirst()
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
			NodeLL* newHead = head->nextNode;
			newHead->previousNode = nullptr;
			delete head;
			head = newHead;
		}
	}

	void DeleteByValue(std::string value)
	{
		if (isEmpty()) return;
		if (GetSize() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}

		NodeLL* current = head;
		while (current->value != value)
		{
			current = current->nextNode;
		}
		if (current == head)
		{
			DeleteFirst();
		}
		else if (current == tail)
		{
			DeleteLast();
		}
		else
		{
			NodeLL* previos = current->previousNode;
			NodeLL* next = current->nextNode;
			previos->nextNode = next;
			next->previousNode = previos;
			delete current;
		}

	}

	NodeLL* Find(std::string value)
	{
		NodeLL* currentNode = head;
		while (currentNode)
		{
			if (currentNode->value == value)
			{
				return currentNode;
			}
			currentNode = currentNode->nextNode;
		}
		return nullptr;
	}

	void Print()
	{
		NodeLL* currentNode = head;
		while (currentNode)
		{
			std::cout << currentNode->value << " ";
			currentNode = currentNode->nextNode;
		}
		std::cout << std::endl;
	}
};
