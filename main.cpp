#include <iostream>
#include <string>
using namespace std;

// Структура для хранения связанных списков внутри бакетов
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
    uint32_t capacity;
    Hbuckets<T>* arr;

    uint32_t hash(const string& value)
    {
        uint32_t hash = 5381;
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
        uint32_t index = hash(key);  // Получаем индекс
        arr[index].push_back(key, value);  // Добавляем элемент в соответствующий бакет
    }

    // Метод получения элемента по ключу
    T HGET(const string& key)
    {
        uint32_t index = hash(key);  // Получаем индекс
        return arr[index].get(key);  // Ищем элемент в соответствующем бакете
    }

    
    void HDEL(const string& key)
    {
        uint32_t index = hash(key);  // Получаем индекс
        arr[index].remove(key);  // Удаляем элемент из соответствующего бакета
    }

    // Печать всех бакетов
    void print()
    {
        for (uint32_t i = 0; i < capacity; ++i)
        {
            cout << "Bucket " << i << ": ";
            arr[i].print();
        }
    }

    ~HASHtable()
    {
        delete[] arr;
    }
};

int main()
{
    
    HASHtable<int> tablica(10);

    
    tablica.HSET("ALICE", 1);
    tablica.HSET("BOB", 2);
    tablica.HSET("CHARLIE", 3);
    tablica.HSET("DAVID", 4);

    
    cout << "Hash Table:" << endl;
    tablica.print();

    cout << "Get value for key 'BOB': " << tablica.HGET("BOB") << endl;

    
    tablica.HDEL("CHARLIE");
    cout << "After deleting 'CHARLIE':" << endl;
    tablica.print();

    return 0;
}