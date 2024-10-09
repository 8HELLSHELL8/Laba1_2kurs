#pragma once
#include <cmath>
#include <iostream>
#include <fstream>

template<typename T>
struct NodeQUT
{
	T value;
	NodeQUT<T>* nextNode;
};

template<typename T>
struct QueueT
{
private:
	NodeQUT<T>* head;
	NodeQUT<T>* tail;
public:
	QueueT() : head(nullptr), tail(nullptr) {}

	~QueueT()
	{
		NodeQUT<T>* currentNode = head;
		while (currentNode)
		{
			NodeQUT<T>* curNext = currentNode->nextNode;
			//delete currentNode;
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
		NodeQUT<T>* currentNode = head;
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
		NodeQUT<T>* newNode = new NodeQUT<T>{ value, nullptr };
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

		NodeQUT<T>* newHead = head->nextNode;
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
		NodeQUT<T>* currentNode = head;
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

		NodeQUT<T>* currentNode = head;
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

		NodeQUT<T>* currentNode = head;
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

};



struct node
{
	int32_t key;
	node* previous;
	node* leftChild;
	node* rightChild;
	node(int value)
	{
		this->key = value;
		previous = nullptr;
		leftChild = nullptr;
		rightChild = nullptr;
	}
};

struct FBT
{
private:
	node* root;
	QueueT<node*> waitlist;
	QueueT<node*> allNodes;
public:
	FBT(int32_t value)
	{
		root = new node(value);
		allNodes.Enqueue(root);
		waitlist.Enqueue(root);
	}

	void Add(int32_t value)
	{
		node* parent = waitlist.Front(); // Берем узел, который находится в очереди

		node* newNode = new node{ value };
		allNodes.Enqueue(newNode);

		// Проверяем, куда добавить новый узел
		if (parent->leftChild == nullptr) parent->leftChild = newNode;
		else if (parent->rightChild == nullptr)
		{
			parent->rightChild = newNode;
			waitlist.Dequeue(); // Если у узла есть оба ребенка, удаляем его из очереди
		}

		waitlist.Enqueue(newNode);
	}

	void PrintNodes()
	{
		for (size_t i = 0; i < allNodes.GetSize(); i++) std::cout << allNodes[i]->key << " ";
		std::cout << std::endl;
	}

	void PrintTree()
	{
		int totalNodes = allNodes.GetSize();  // Общее количество узлов в дереве
		int level = 0;                        // Текущий уровень дерева
		int printedNodes = 0;                 // Количество уже напечатанных узлов
		int maxNodesAtLevel = std::pow(2, std::floor(std::log2(totalNodes)) + 1);
		// Печатаем дерево по уровням
		while (printedNodes < totalNodes)
		{
			// Количество узлов на текущем уровне — 2^level
			int nodesInLevel = pow(2, level);
			level++;  // Переходим к следующему уровню

			int leadingSpaces = maxNodesAtLevel / nodesInLevel - 1;
			int spacingBetweenNodes = maxNodesAtLevel / nodesInLevel - 1;
			std::string leadSep(leadingSpaces + 3, ' ');
			std::string endSep(spacingBetweenNodes, ' ');
			// Печатаем узлы текущего уровня
			for (int i = 0; i < nodesInLevel && printedNodes < totalNodes; i++)
			{

				std::cout << leadSep << allNodes[printedNodes]->key << endSep;
				printedNodes++;
			}

			std::cout << std::endl;  // Переход на новый уровень
		}
	}

	void PrintInFile(std::fstream& file)
	{
		int totalNodes = allNodes.GetSize();  // Общее количество узлов в дереве
		int level = 0;                        // Текущий уровень дерева
		int printedNodes = 0;                 // Количество уже напечатанных узлов
		int maxNodesAtLevel = std::pow(2, std::floor(std::log2(totalNodes)) + 1);
		// Печатаем дерево по уровням
		while (printedNodes < totalNodes)
		{
			// Количество узлов на текущем уровне — 2^level
			int nodesInLevel = pow(2, level);
			level++;  // Переходим к следующему уровню

			int leadingSpaces = maxNodesAtLevel / nodesInLevel - 1;
			int spacingBetweenNodes = maxNodesAtLevel / nodesInLevel - 1;
			std::string leadSep(leadingSpaces + 3, ' ');
			std::string endSep(spacingBetweenNodes, ' ');
			// Печатаем узлы текущего уровня
			for (int i = 0; i < nodesInLevel && printedNodes < totalNodes; i++)
			{

				file << leadSep << allNodes[printedNodes]->key << endSep;
				printedNodes++;
			}

			file << std::endl;  // Переход на новый уровень
		}
	}


	node* findPlace(int value)
	{
		for (size_t i = 0; i < allNodes.GetSize(); i++)
		{
			if (allNodes[i]->key == value)
			{
				return allNodes[i];
			}
		}
		std::cout << "Value does not exists!" << std::endl;
		return nullptr;
	}

	bool isFull()
	{
		for (size_t i = 0; i < allNodes.GetSize(); i++)
		{
			if (allNodes[i]->leftChild == nullptr && allNodes[i]->rightChild != nullptr ||
				allNodes[i]->leftChild != nullptr && allNodes[i]->rightChild == nullptr) return false;

		}
		return true;
	}
};