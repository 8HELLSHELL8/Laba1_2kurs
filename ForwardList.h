#pragma once

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

	NodeFL* head;
	NodeFL* tail;

public:

	ForwardList(T value)
	{
		NodeFL* startNode = new NodeFL{ value, nullptr };
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
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	int Size()
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

	void AddToEnd(T value)
	{
		NodeFL* newNode = new NodeFL{ value, nullptr };
		tail->next = newNode;
		tail = newNode;
	}

	void AddToStart(T value)
	{
		NodeFL* newNode = new NodeFL{ value, head };
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

	void DeleteFirst()
	{
		if (isEmpty()) return;
		if (Size() == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		NodeFL* temp = head;
		head = head->next;
		delete temp;
	}

	void DeleteByValue(T value)
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

	NodeFL* Find(T value)
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

	void Print()
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
};

















