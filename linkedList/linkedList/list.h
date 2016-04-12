#pragma once

#include <iostream>
#include <sstream>

//==========================================================================
//Singly Linked List
//==========================================================================
class SinglyList
{
private:
	struct node
	{
		int x;
		node* next;
	};

	node* head;
	node* current;
	node* previous;

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
	int size();

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
	struct node
	{
		int x;
		node* next;
		node* prev;

	};

	node* first;
	node* last;
	node* current;

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
	int size();

	//reverse
	//void reverseList();
	//isEmpty
	bool isEmpty();
	//toString
	void printList();
	void printListReverse();
};