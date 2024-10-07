#pragma once

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
	Queue<node*> waitlist;
	Queue<node*> allNodes;
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