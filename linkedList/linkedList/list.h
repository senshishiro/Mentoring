#pragma once

#include <iostream>
#include <sstream>

//==========================================================================
//Nodes
//==========================================================================
class Node
{
public:
		int x;
		Node* next;
};

class DoubleNode
{
public:
	int x;
	DoubleNode* next;
	DoubleNode* prev;
};

//==========================================================================
//Singly Linked List
//==========================================================================
class SinglyList
{
private:

	Node* head;
	int size;
public:
	
	//Constructor
	SinglyList();

	//add
	void addNode(int data);
	//remove
	void deleteNode(int data);
	//delete all
	void deleteAll();

	//size
	int getSize();

	//reverse
	void reverseList();
	//isEmpty
	bool isEmpty();
	//toString
	void printList();
};

//==========================================================================
//Doubly Linked List
//==========================================================================
class DoublyList
{
private:

	DoubleNode* first;
	DoubleNode* last;
	int size;
public:
	//Constructor
	DoublyList();

	//add
	void addNode(int data);
	//remove
	void deleteNode(int data);
	
	//delete all
	void deleteAll();

	//size
	int getSize();

	//reverse
	void reverseList();
	//isEmpty
	bool isEmpty();
	//toString
	void printList();
	void printListReverse();

	//sort

	void sort();
	void swap(DoubleNode* a, DoubleNode* b);
};