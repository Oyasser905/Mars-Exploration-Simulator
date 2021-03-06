#pragma once
#include <iostream>
using namespace std;

//===============================NODE CLASS================================
template < typename T>
class NodeLL
{
private:
	T item; //data item
	NodeLL<T>* next; //pointer to next node
public:
	NodeLL(); //constructor; input()
	NodeLL(const T& r_Item); //constructor; input(item)
	NodeLL(const T& r_Item, NodeLL<T>* nextNodePtr); //constructor; input(item, next)
	void newNode(const T& r_Item); //create a new node
	void newNode(const T& r_Item, NodeLL<T>* nextNodePtr); //create a new node with next pointer
	void setItem(const T& r_Item); //set item data
	void setNext(NodeLL<T>* nextNodePtr); //set next of the node
	T getItem() const; //get the item data of node
	NodeLL<T>* getNext() const; //get next of node
};

//----------Implementation of Node class functions----------
//constructor
template < typename T>
NodeLL<T>::NodeLL()
{
	next = nullptr;
}

//constructor with item
template < typename T>
NodeLL<T>::NodeLL(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

//constructor with item and next
template < typename T>
NodeLL<T>::NodeLL(const T& r_Item, NodeLL<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}

//create a new node without next
template<typename T>
void NodeLL<T>::newNode(const T& r_Item)
{
	Node* nNode = new Node<T> * (r_Item);
	nNode->setItem(r_Item);
	nNode->setNext(NULL);
}

//create a new node with the next
template<typename T>
void NodeLL<T>::newNode(const T& r_Item, NodeLL<T>* nextNodePtr)
{
	NodeLL* NodeLL = new NodeLL<T> * (r_Item);
	nNode->setItem(r_Item);
	nNode->setNext(nextNodePtr);
}

//Function to set item
template < typename T>
void NodeLL<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

//Function to set next
template < typename T>
void NodeLL<T>::setNext(NodeLL<T>* nextNodePtr)
{
	next = nextNodePtr;
}

//Function to get item
template < typename T>
T NodeLL<T>::getItem() const
{
	return item;
}

//Function to get next
template < typename T>
NodeLL<T>* NodeLL<T>::getNext() const
{
	return next;
}

//===============================Linked List Class================================

template <typename T>
class LinkedList
{
private:
	NodeLL<T>* Head;
public:
	LinkedList()
	{
		Head = nullptr;
	}

	~LinkedList()
	{
		DeleteList();
	}

	//To delete all elements inside the list
	void DeleteList()
	{
		NodeLL<T>* ptr = Head;
		while (ptr)
		{
			ptr = Head->getNext();
			delete Head;
			Head = ptr;
		}
	}

	//To delete the first element in the list
	void DeleteBeg()
	{
		if (Head)
		{
			NodeLL<T>* temp = Head;
			Head->setNext(Head->getNext());
			delete temp;
		}
		else
			return;
	}

	//To delete last element in the list
	void DeleteEnd()
	{
		if (Head && Head->getNext())
		{
			NodeLL<T>* temp = Head;
			NodeLL<T>* prev = Head->getNext();
			while (temp->getNext())
			{
				prev = temp;
				temp = temp->getNext();
			}
			prev->setNext(nullptr);
			delete temp;
		}
		else if (Head)
		{
			NodeLL<T>* temp = Head;
			Head = nullptr;
			delete temp;
		}
		else
			return;
	}

	//To take inputs of the list from the user
	void CreateList()
	{
		int value;
		cin >> value;
		while (value != -1)
		{
			this->InsertEnd(value);
			cin >> value;
		}
	}

	//To insert a new element at the end of the list
	void InsertEnd(const T& data)
	{
		NodeLL<T>* ptr = newNode(data);
		if (Head)
		{
			NodeLL<T>* ptr2 = Head;
			while (ptr2->getNext())
				ptr2 = ptr2->getNext();
			ptr2->setNext(ptr);
		}
		else
		{
			Head = ptr;
		}
	}

	void InsertBeg(const T& data)
	{
		NodeLL<T>* ptr = new NodeLL<T>(data);
		if (Head)
		{
			ptr->setNext(Head);
			Head = ptr;
		}
		else
		{
			Head = ptr;
		}
	}

	void PrintList() const
	{
		if (Head)
		{
			NodeLL<T>* ptr = Head;
			while (ptr)
			{
				cout << ptr->getItem() << " ";
				ptr = ptr->getNext();
			}
			cout << endl;
		}
		else
			return;
	}
};

