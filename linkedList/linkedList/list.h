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

class Double_Node
{
public:
	int x;
	Double_Node* next;
	Double_Node* prev;
};

//==========================================================================
//Singly Linked List
//==========================================================================
class SinglyList
{
private:

	Node* head;
	Node* current;
	Node* previous;

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

	Double_Node* first;
	Double_Node* last;
	Double_Node* current;

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
	void reverseList();
	//isEmpty
	bool isEmpty();
	//toString
	void printList();
	void printListReverse();
};