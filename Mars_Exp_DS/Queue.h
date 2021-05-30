#pragma once
#include <iostream>
using namespace std;

//===============================NODE CLASS================================
template < typename T>
class NodeQ
{
private:
	T item; //data item
	NodeQ<T>* next; //pointer to next node
public:
	NodeQ(); //constructor; input()
	NodeQ(const T& r_Item); //constructor; input(item)
	NodeQ(const T& r_Item, NodeQ<T>* nextNodePtr); //constructor; input(item, next)
	void newNode(const T& r_Item); //create a new node
	void newNode(const T& r_Item, NodeQ<T>* nextNodePtr); //create a new node with next pointer
	void setItem(const T& r_Item); //set item data
	void setNext(NodeQ<T>* nextNodePtr); //set next of the node
	T getItem() const; //get the item data of node
	NodeQ<T>* getNext() const; //get next of node
}; 

//----------Implementation of Node class functions----------
//constructor
template < typename T>
NodeQ<T>::NodeQ()
{
	next = nullptr;
}

//constructor with item
template < typename T>
NodeQ<T>::NodeQ(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

//constructor with item and next
template < typename T>
NodeQ<T>::NodeQ(const T& r_Item, NodeQ<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}

//create a new node without next
template<typename T>
void NodeQ<T>::newNode(const T& r_Item)
{
	NodeQ* nNode = new NodeQ<T>*(r_Item);
	nNode->setItem(r_Item);
	nNode->setNext(NULL) ;
}

//create a new node with the next
template<typename T>
void NodeQ<T>::newNode(const T& r_Item, NodeQ<T>* nextNodePtr)
{
	Node* nNode = new NodeQ<T>*(r_Item);
	nNode->setItem(r_Item);
	nNode->setNext(nextNodePtr);
}

//Function to set item
template < typename T>
void NodeQ<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

//Function to set next
template < typename T>
void NodeQ<T>::setNext(NodeQ<T>* nextNodePtr)
{
	next = nextNodePtr;
}

//Function to get item
template < typename T>
T NodeQ<T>::getItem() const
{
	return item;
}

//Function to get next
template < typename T>
NodeQ<T>* NodeQ<T>::getNext() const
{
	return next;
}

//===============================QUEUE CLASS================================
template <typename T>
class LinkedQueue
{
private:
	int size = 0;
	NodeQ<T>* backPtr;
	NodeQ<T>* frontPtr;
public:
	LinkedQueue(); //constructor
	int getSize() const; //get size of queue
	bool isEmpty() const; //check is queue is empty
	bool enqueue(const T& newEntry); //enqueue queue; returns true if enqueued
	bool dequeue(T& frntEntry); //dequeue queue; returns true if dequeued
	bool peek(T& frntEntry)  const; //gets item of the frontptr; returns true if it's not empty
	void print() const; //prints queue
	LinkedQueue(const LinkedQueue<T>& LQ);//copy constructor
	~LinkedQueue(); //destructor
};

//----------Implementation of Queue class functions----------
//constructor
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

//Function to get the size
template<typename T>
int LinkedQueue<T>::getSize() const
{
	return size;
}

//isEmpty; Sees whether this priority queue is empty.
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

//Enqueue; Adds newEntry at the back of this priority queue.
template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	NodeQ<T>* newNodePtr = new NodeQ<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	size++;
	return true;
} // end enqueue

//Dequeue; Removes the front of this queue. That is, removes the item that was added earliest.
template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodeQ<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	size--;
	return true;
}

// Peek; gets item of the front item; returns true if it's not empty
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

//Destructor; removes all nodes from the queue by dequeuing them
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

//copy constructor
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	NodeQ<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	NodeQ<T>* ptr = new NodeQ<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		NodeQ<T>* ptr = new NodeQ<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

//Function to print queue
template<typename T>
void LinkedQueue<T>::print() const
{
	NodeQ<T>* ptr = frontPtr;
	while (ptr)
	{
		cout << ptr->getItem() << " ";
		ptr = ptr->getNext();
	}
	cout << endl;
}