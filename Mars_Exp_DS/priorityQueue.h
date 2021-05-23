#pragma once
//Priority Queue using Linked List
#include<iostream>
using namespace std;

//===============================NODE CLASS================================
template < typename T>
class Node
{
private:
	T item; // A data item
	int priority; // Higher values indicate higher priority
	Node<T>* next; // Pointer to next node
public:
	Node();
	Node(const T& r_Item, int pr);
	Node(const T& r_Item, Node<T>* nextNodePtr, int pr);
	Node<T>* newNode(const T& r_Item, int pr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	int getPriority() const;
	Node<T>* getNext() const;
};

//Implementation of Node class functions
template < typename T>
Node<T>::Node()
{
	next = nullptr;
}
template < typename T>
Node<T>::Node(const T& r_Item, int pr)
{
	item = r_Item;
	priority = pr;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr, int pr)
{
	item = r_Item;
	priority = pr;
	next = nextNodePtr;
}

// Function to create a new node
template < typename T>
Node<T>* Node<T>::newNode(const T& r_Item, int pr)
{
	Node* nNode = new Node<T>*(r_Item, pr);
	nNode->item = r_Item;
	nNode->priority = pr;
	nNode->next = NULL;

	return temp;
}

// Function to set item or data of Node
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

// Set next function
template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

// Get Item function
template < typename T>
T Node<T>::getItem() const
{
	return item;
}

// Get Priority number function
template < typename T>
int Node<T>::getPriority() const
{
	return priority;
}

// Get next function
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
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int pr);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void print() const;
	~PriorityQueue();

	//copy constructor
	PriorityQueue(const PriorityQueue<T>& PQ);
};


//The constructor of the Priority Queue class.
template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}
/*
Function: isEmpty
Sees whether this priority queue is empty.

Input: None.
Output: True if the priority queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/*Function:enqueue
Adds newEntry at the back of this priority queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
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
	return true;
} 

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
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
	return true;
}

// Return the value at head
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

/*
Function: destructor
removes all nodes from the priority queue by dequeuing them
*/
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the priority queue
	while (dequeue(temp));
}

/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: PriorityQueue<T>: The Priority Queue to be copied
Output: none
*/
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
