#include <iostream>
#include "Header.h"
using namespace std;

struct NodeLL
{
	string value;
	NodeLL* previousNode;
	NodeLL* nextNode;
};

struct LinkedList
{
private:
	NodeLL* tail;
	NodeLL* head;
public:

	LinkedList(string value)
	{
		NodeLL* startNode = new NodeLL{ value, nullptr, nullptr };
		head = startNode;
		tail = startNode;
		
	}

};


int main()
{
	
	return 0;
}