#pragma once
#include<iostream>
using namespace std;

//===============================NODE CLASS================================
template < typename T>
class Node
{
private:
	T item; //data item
	int priority; //higher values indicate higher priority
	Node<T>* next; //pointer to next node
public:
	Node(); //constructor; no input
	Node(const T& r_Item, int pr); //constructor; input(item, priority)
	Node(const T& r_Item, int pr, Node<T>* nextNodePtr); //constructor; input(item, priority, next)
	void newNode(const T& r_Item, int pr); //create a new node
	void newNode(const T& r_Item, int pr, Node<T>* nextNodePtr); //create a new node with next pointer
	void setItem(const T& r_Item); //set item data
	void setPriority(int pr); //set item data
	void setNext(Node<T>* nextNodePtr); //set next of the node
	T getItem() const; //get the item data of node
	int getPriority() const; //get priority data of node
	Node<T>* getNext() const; //get next of node
};

//----------Implementation of Node class functions----------
//constructor
template < typename T>
Node<T>::Node()
{
	next = nullptr;
}
//constructor with item and priority 
template < typename T>
Node<T>::Node(const T& r_Item, int pr)
{
	item = r_Item;
	priority = pr;
	next = nullptr;
}
//constructor with item, priority, and next
template < typename T>
Node<T>::Node(const T& r_Item, int pr, Node<T>* nextNodePtr)
{
	item = r_Item;
	priority = pr;
	next = nextNodePtr;
}

//Function to create a new node without the next
template < typename T>
void Node<T>::newNode(const T& r_Item, int pr)
{
	Node* nNode = new Node<T>*(r_Item, pr);
	nNode->setNext(NULL);
}

//Function to Create new node with the next 
template<typename T>
void Node<T>::newNode(const T& r_Item, int pr, Node<T>* nextNodePtr)
{
	Node* nNode = new Node<T>*(r_Item);
	nNode->setItem(r_Item);
	nNode->getPriority(pr);
	nNode->setNext(nextNodePtr);
}

//Function to set priority
template<typename T>
void Node<T>::setPriority(int pr)
{
	priority = pr;
}

//Function to set item data of Node
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

//Set next function
template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

//Get Item function
template < typename T>
T Node<T>::getItem() const
{
	return item;
}

//Get Priority function
template < typename T>
int Node<T>::getPriority() const
{
	return priority;
}

//Get next function
template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

//===============================PRIORITY QUEUE CLASS================================
template <typename T>
class PriorityQueue
{
private:
	Node<T>* backPtr; //back pointer
	Node<T>* frontPtr; //front pointer
	int size; //size of the queue
public:
	PriorityQueue(); //constructor
	bool isEmpty() const; //check is queue is empty
	bool enqueue(const T& newEntry, int pr); //enqueue queue; returns true if enqueued
	bool dequeue(T& frntEntry); //dequeue queue; returns true if dequeued
	int getSize() const; //get size of queue
	bool peek(T& frntEntry)  const; //gets item of the frontptr; returns true if it's not empty
	void print() const; //prints queue
	PriorityQueue(const PriorityQueue<T>& PQ);//copy constructor
	~PriorityQueue(); //destructor
};

//----------Implementation of Priority Queue class functions----------
//The constructor of the Priority Queue class.
template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

//isEmpty; Sees whether this priority queue is empty.
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

//Enqueue; Adds newEntry at the back of this priority queue.
template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, int pr)
{
	Node<T>* newNodePtr = newNode(newEntry, pr);
	// Insert the new node
	if (isEmpty()) //special case if this is the first node to insert
	{
		frontPtr = newNodePtr; // The queue is empty
	}
	if (newNodePtr->getPriority() > frontPtr->getPriority())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else
	{
		Node<T> *current;
		while (current)
		{
			if (newNodePtr->getPriority() >= current->getPriority())
			{
				newNodePtr->setNext() = current->getNext();
				current->setNext() = newNodePtr;
			}
			current = current->getNext();
		}
	}
	size++;
	return true;
} 

//Dequeue; Removes the front of this queue. That is, removes the item that was added earliest.
template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
	{
		return false;
	}

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr) // Special case: last node in the queue
	{
		backPtr = nullptr;
	}

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	size--;
	return true;
}

template<typename T>
int PriorityQueue<T>::getSize() const
{
	return size;
}

// Peek; gets item of the front item; returns true if it's not empty
template <typename T>
bool PriorityQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
	{
		return false;
	}
	frntEntry = frontPtr->getItem();
	return true;
}

//Destructor removes all nodes from the priority queue by dequeuing them
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	T temp;

	
	while (dequeue(temp))//Dequeue all nodes in the priority queue
}

//Print function; prints all of the queue
template<typename T>
void PriorityQueue<T>::print() const
{
	Node<T>* ptr = frontPtr;
	while (ptr)
	{
		cout << ptr->getItem() << " ";
		ptr = ptr->getNext();
	}
	cout << endl;
}

//Copy constructor
template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& PQ)
{
	Node<T>* NodePtr = PQ.frontPtr;
	if (!NodePtr) //PQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem(), NodePtr->getPriority());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem(), NodePtr->getPriority());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}