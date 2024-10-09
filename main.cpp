#include <iostream>
#include <fstream>
#include <string>
#include "Array.h"
#include "ForwardList.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "TreeFULL.h"
using namespace std;



template<typename T>
struct Hbuckets
{
private:
	// Узел для хранения данных
	template<typename U>
	struct Node
	{
		string key;       // Ключ
		T value;          // Значение
		Node<U>* next;    // Указатель на следующий узел

		Node(const string& key, const T& value) : key(key), value(value), next(nullptr) {}
	};

	Node<T>* head;    // Голова списка
	Node<T>* tail;    // Хвост списка

public:
	Hbuckets() : head(nullptr), tail(nullptr) {}

	bool isEmpty()
	{
		return head == nullptr;
	}

	T get(const string& key)
	{
		Node<T>* tempNode = head;
		while (tempNode && tempNode->key != key) tempNode = tempNode->next;
		if (tempNode && tempNode->key == key)
			return tempNode->value;
		throw runtime_error("Key not found");
	}

	void push_back(const string& key, const T& value)
	{
		Node<T>* newNode = new Node<T>(key, value);
		if (isEmpty())
		{
			head = newNode;
			tail = newNode;
			return;
		}
		tail->next = newNode;
		tail = newNode;
	}

	void remove(const string& key)
	{
		if (isEmpty()) return;

		if (head->key == key)
		{
			Node<T>* temp = head;
			head = head->next;
			delete temp;

			if (head == nullptr) tail = nullptr;

			return;
		}

		Node<T>* prev = head;
		Node<T>* current = head->next;

		while (current != nullptr)
		{
			if (current->key == key)
			{
				prev->next = current->next;
				if (current == tail) tail = prev;
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
	}

	void print()
	{
		if (isEmpty()) return;
		Node<T>* currentNode = head;
		while (currentNode)
		{
			cout << "[" << currentNode->key << ": " << currentNode->value << "] ";
			currentNode = currentNode->next;
		}
		cout << endl;
	}
};


template<typename T>
struct HASHtable
{
private:
	int capacity;
	Hbuckets<T>* arr;

	int16_t hash(const string& value)
	{
		int hash = 5381;
		for (char c : value)
		{
			hash = ((hash << 5) + hash) + c;
		}
		return hash % capacity;
	}

public:
	HASHtable(int capacityValue)
	{
		arr = new Hbuckets<T>[capacityValue];  // Выделяем массив бакетов
		capacity = capacityValue;
	}

	// Метод вставки элемента
	void HSET(const string& key, const T& value)
	{
		int index = hash(key);  // Получаем индекс
		arr[index].push_back(key, value);  // Добавляем элемент в соответствующий бакет
	}

	// Метод получения элемента по ключу
	T HGET(const string& key)
	{
		int index = hash(key);  // Получаем индекс
		return arr[index].get(key);  // Ищем элемент в соответствующем бакете
	}


	void HDEL(const string& key)
	{
		int index = hash(key);  // Получаем индекс
		arr[index].remove(key);  // Удаляем элемент из соответствующего бакета
	}

	// Печать всех бакетов
	void print()
	{
		for (int i = 0; i < capacity; ++i)
		{
			cout << "Bucket " << i << ": ";
			arr[i].print();
			cout << endl;
		}
	}

	void PrintInFile(fstream& file)
	{
		for (int i = 0; i < capacity; ++i)
		{
			file << "Bucket " << i << ": ";
			arr[i].print();
			file << endl;
		}
	}

	~HASHtable()
	{
		delete[] arr;
	}
};


void handleCommand(int argc, char** argv)
{
	for (int i = 0; i < argc; i++)
	{

		cout << argv[i] << " ";
	}

	if (argv[1] == "--file")
	{
		cout << "Wrong syntax" << endl;
		exit(-1);
	}
	string fileName = argv[2];

	fstream myfile(fileName);
	if (!myfile.is_open())
	{
		cout << "Cannot find file!" << endl;
		exit(-1);
	}


	string fileContent;
	Array<string> contentArray;
	while (getline(myfile, fileContent, ','))
	{
		contentArray.push_back(fileContent);
	}

	if (argv[3] == "--query")
	{
		cout << "Wrong syntax" << endl;
		exit(-1);
	}

	if (argc == 3)
	{
		cout << "Wrong syntax" << endl;
		exit(-1);
	}
	else if (&argv[4][0] == "M" || argv[4] == "PRINT")
	{
		Array<string> contentArray;
		if (argv[4] == "MPUSH")
		{
			if (argv[5] == "Array")
			{
				if (argc == 8) contentArray.push_back(argv[6], stoi(argv[7]));
				else contentArray.push_back(argv[5]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "MDEL")
		{
			if (argv[5] == "Array")
			{
				if (argc == 7) contentArray.pop(stoi(argv[6]));
				else contentArray.pop();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "MGET")
		{
			if (argv[5] == "Array")
			{
				contentArray.printInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "Array")
			{
				contentArray.print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}

	}
	else if (&argv[4][0] == "F")
	{
		string first = contentArray[0];
		ForwardList<string> content{ first };
		for (int i = 1; i < contentArray.getSize(); i++)
		{
			content.push_back(contentArray[i]);
		}

		if (argv[4] == "FLPUSH")
		{
			if (argv[5] == "FList")
			{
				if (argc == 8) content.push_back(argv[5], stoi(argv[6]));
				else contentArray.push_back(argv[5]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "FLDEL")
		{
			if (argv[5] == "FList")
			{
				if (argc == 7) content.Pop(stoi(argv[6]));
				else content.Pop();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "FLGET")
		{
			if (argv[5] == "FList")
			{
				content.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "FList")
			{
				content.Print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}

	}
	else if (&argv[4][0] == "L")
	{
		LinkedList content{ contentArray[0] };
		for (int i = 1; i < contentArray.getSize(); i++)
		{
			content.push_back(contentArray[i]);
		}
		if (argv[4] == "LLPUSH")
		{
			if (argv[5] == "LList")
			{
				if (argc == 8) content.push_back(argv[5], stoi(argv[6]));
				else content.push_back(argv[5]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "LLDEL")
		{
			if (argv[5] == "LList")
			{
				if (argc == 7) content.Pop(stoi(argv[6]));
				else content.Pop();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "LLGET")
		{
			if (argv[5] == "LList")
			{
				content.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "LList")
			{
				content.Print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
	}
	else if (&argv[4][0] == "Q")
	{
		Queue<string> content;
		for (int i = 0; i < contentArray.getSize(); i++)
		{
			content.Enqueue(contentArray[i]);
		}
		if (argv[4] == "QPUSH")
		{
			if (argv[5] == "Queue")
			{
				content.Enqueue(argv[6]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "QDEL")
		{
			if (argv[5] == "Queue")
			{
				content.Dequeue();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "QGET")
		{
			if (argv[5] == "Queue")
			{
				content.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "Queue")
			{
				content.Print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
	}
	else if (&argv[4][0] == "S")
	{
		Stack<string> content;
		for (int i = 0; i < contentArray.getSize(); i++)
		{
			content.Push_back(contentArray[i]);
		}
		if (argv[4] == "SPUSH")
		{
			if (argv[5] == "Stack")
			{
				content.Push_back(argv[6]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "SDEL")
		{
			if (argv[5] == "Stack")
			{
				content.Pop();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "SGET")
		{
			if (argv[5] == "Stack")
			{
				content.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "Stack")
			{
				content.Print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
	}
	else if (&argv[4][0] == "H")
	{
		HASHtable<string> content{ 50 };
		for (int i = 0, j = 10; i < contentArray.getSize(); i++, j++)
		{
			content.HSET(to_string(j), to_string(i));
		}
		if (argv[4] == "HSET")
		{
			if (argv[5] == "HASH")
			{
				content.HSET(argv[6], argv[7]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "HDEL")
		{
			if (argv[5] == "HASH")
			{
				content.HDEL(argv[6]);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "HGET")
		{
			if (argv[5] == "HASH")
			{
				content.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "HASH")
			{
				content.print();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
	}
	else if (&argv[4][0] == "T")
	{
		FBT tree{ stoi(contentArray[0]) };
		for (int i = 1; i < contentArray.getSize(); i++)
		{
			tree.Add(stoi(contentArray[i]));
		}

		if (argv[4] == "TPUSH")
		{
			if (argv[5] == "Tree")
			{
				tree.Add(stoi(argv[6]));
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "TISFULL")
		{
			if (argv[5] == "Tree")
			{
				tree.isFull();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);

		}
		else if (argv[4] == "TGET")
		{
			if (argv[5] == "Tree")
			{
				tree.PrintInFile(myfile);
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
		else if (argv[4] == "PRINT")
		{
			if (argv[5] == "Tree")
			{
				tree.PrintTree();
				return;
			}
			cout << "Wrong syntax" << endl;
			exit(-1);
		}
	}
	else
	{
		cout << "Wrong syntax!" << endl;
		exit(-1);
	}
}




int main(int argc, char** argv)
{


	handleCommand(argc, argv);

	return 0;
}