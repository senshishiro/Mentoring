
#include "stdafx.h"
#include "list.h"

using namespace std;

//==========================================================================
//Singly Linked List
//==========================================================================

//--------------------------------------------------------
//Constructor

SinglyList::SinglyList()
{
	head = NULL;
	size = 0;
}

//--------------------------------------------------------
//addNode
//BigO Analysis: O(N) - Goes through the list looking for the last node. Appends node at the end
void SinglyList::addNode(int data)
{
	//create node
	Node* n = new Node;
	Node* current = head;
	n->x = data;
	n->next = NULL;
	

	//if a list already exists
	if (head != NULL)
	{
		//current = head;

		//search for the last node of the list
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = n;
		size++;
	}
	//set to head if a node doesn't exist 
	else
	{
		head = n;
		size++;
	}
}

//--------------------------------------------------------
//deleteNode
//BigO Analysis: O(N) - loops through the linked list once looking for matching value

void SinglyList::deleteNode(int data)
{
	Node* current = head;
	Node* previous = head;

	//find node
	while (current != NULL && current->x != data)
	{
		previous = current;
		current = current->next;
	}


	//print error if there are no matches
	if (current == NULL)
	{
		cerr << "error: " << data << " does not exist in the list.\n";
	}
	else
	{
		//update head if the first node is deleted
		if (current == head)
		{
			head = head->next;
		}

		previous->next = current->next;
		delete current;
		size--;
		cout << data << " was deleted from the list.\n";
	}	
}

//--------------------------------------------------------
//deleteAll - Goes through each node and deletes it
//BigO Analysis: O(N) - Only loops through once deleting each node.
void SinglyList::deleteAll()
{
	Node* current = head;

	while (current != NULL)
	{
		head = current->next;
		delete current;
		current = head;
	}

	//cout << "List has been emptied\n";
	head = NULL;
	size = 0;
}

//--------------------------------------------------------
// reverse list
//BigO Analysis: O(N) - Loops through the list rebuilding it in reverse
void SinglyList::reverseList()
{
	Node* temp = NULL;

	Node* current = head;
	Node* previous = NULL;
	
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		temp->next = previous;
		previous = temp;
	}
	
	//makes the last node in the loop the head
	head = previous;

}
//--------------------------------------------------------
//printList
//BigO Analysis: O(N) - loops throught the list, and prints out data
void SinglyList::printList()
{
	Node* current = head;
	if (isEmpty())
	{
		cout << "The list is empty\n";
	}
	else
	{
		cout << "------------------\n";
		while (current != NULL)
		{
			cout << current->x << endl;
			current = current->next;
		}
		cout << "------------------\n";
	}
}

//--------------------------------------------------------
//size
//BigO Analysis: O(N) - Loops through linked list counting all the nodes

int SinglyList::getSize()
{
	return size; 
}

//--------------------------------------------------------
//isEmpty
//BigO Analysis: O(1) - Checks if there is a head node
bool SinglyList::isEmpty()
{
	if (head == NULL)
	{
		return true;
	}		
	else
	{
		return false;
	}		
}


//==========================================================================
//Doubly Linked List
//==========================================================================

//--------------------------------------------------------
//Constructor
DoublyList::DoublyList()
{
	first = NULL;
	last = NULL;
	size = 0;
}

//--------------------------------------------------------
//addNode - adds node to the end of the list
//BigO: O(1) - No loops. appends node to last. 
void DoublyList::addNode(int data)
{
	//create node
	DoubleNode* n = new DoubleNode;
	n->x = data;
	n->next = NULL;
	n->prev = NULL;

	if (first != NULL)
	{
		//Add nodes to the end of the list
		last->next = n;
		n->prev = last;
		last = n;
		
	}
	else
	{
		//first node in the list. set first and last.
		first = n;
		last = n;
	}
	size++;

}
//--------------------------------------------------------
//deleteNode
//BigO: O(N) - one loop that searches for the matching data to delete

void DoublyList::deleteNode(int data)
{
	DoubleNode* endCurrent = last;
	DoubleNode* current = first;
	

	//search for node wioth matching data in the list - one pointer at the beginning and end, moving towards the middle.
	while (current != NULL && current->x != data )
	{
		if (endCurrent->x == data)
		{
			//stop search when they reach the middle
			current = endCurrent;
			break;
		}
		else if (current == endCurrent)
		{
			current = NULL;
			break;
		}
		current = current->next;
		endCurrent = endCurrent->prev;
	}

	// No match value - value does not exist in the list
	if (current == NULL)
	{
		cerr << "error: " << data << " does not exist in the list.\n";
		//delete delNode;
	}
	else
	{
		//delNode = current;

		//reaasign first node when it is about to be deleted
		if (current == first)
		{
			first = first->next;
			first->prev = NULL;
		}
		//reaasign last node when it is about to be deleted
		else if (current == last)
		{
			last = last->prev;
			last->next = NULL;
		}
		else
		{
			//Connect the two nodes adjacent to the deleted node
			(current->next)->prev = current->prev;
			(current->prev)->next = current->next;
		}

		delete current;
		size--;
		cout << data << " was deleted from the list.\n";
	}
}

//--------------------------------------------------------
//deleteAll
//BigO: O(N) - One loop that goes through each node in the list and delete it
void DoublyList::deleteAll()
{
	DoubleNode* current = first;

	while (current != NULL)
	{
		first = first->next;
		delete current;
		current = first;
	}

	//reset nodes
	first = NULL;
	last = NULL;
	size = 0;
}

//--------------------------------------------------------
// reverseList
//BigO Analysis: O(N) - Loops through the list swapping the prev and next pointers
void DoublyList::reverseList()
{
	DoubleNode* previous = NULL;
	DoubleNode* current = first;

	while (current != NULL)
	{
		//swap previous and next pointers
		previous = current->prev;
		current->prev = current->next;
		current->next = previous;
		
		//update the first node to last
		if (current->next == NULL)
		{
			last = current;
			//cout << "set last: "<< current->x << "\n";
		}
		//update the last node to first
		else if (current->prev == NULL)
		{
			first = current;
			//cout << "set first: " << current->x << "\n";
		}
		//advanced pointer by going "backwards", since they were flipped
		current = current->prev;
	}
}


//--------------------------------------------------------
//printList - prints from first node to last.
//BigO: O(N) - one loop goes through each loop, and prints out the data.
void DoublyList::printList()
{
	DoubleNode* current = first;
	if (isEmpty())
	{
		cout << "The list is empty\n";
	}
	else
	{
		cout << "------------------\n";
		while (current != NULL)
		{
			cout << current->x << endl;
			current = current->next;
		}
		cout << "------------------\n";
	}
}


//--------------------------------------------------------
//printListReverse - print from last node to first.
//BigO: O(N) - one loop goes through each loop, and prints out the data.
void DoublyList::printListReverse()
{
	DoubleNode* current = last;
	if (isEmpty())
	{
		cout << "The list is empty\n";
	}
	else
	{
		cout << "------------------\n";
		while (current != NULL)
		{
			cout << current->x << endl;
			current = current->prev;
		}
		cout << "------------------\n";
	}
}


//--------------------------------------------------------
//size
//BigO Analysis: O(1) - calls size from class

int DoublyList::getSize()
{
	return size;
}

//--------------------------------------------------------
//isEmpty
//BigO: O(1) - one comparison that checks if the first node exists.
bool DoublyList::isEmpty()
{
	if (first == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
//--------------------------------------------------------
//swap
//BigO:

void DoublyList::swap(DoubleNode* a, DoubleNode* b)
{
	DoubleNode* temp = new DoubleNode;
	cout << "first " << a->x << " second "<< b->x <<endl;
	cout << "first " << a->next << " second " << b->next << endl;
	
	
	//temp = a;
	temp->prev = a->prev;
	temp->next = a->next;
	

	//a->x = b->x;
	a->prev = b->prev;
	a->next = b->next;

	//b = temp;
	b->prev = temp->prev;
	b->next = temp->next;

	//delete temp;
	cout << "first " << a->x << " second " << b->x << endl;
	cout << "first " << a->next << " second " << b->next << endl;

}


//--------------------------------------------------------
//sort
//BigO:


void DoublyList::sort()
{
	DoubleNode* current = first;
	DoubleNode* inner = first;
	DoubleNode* min = first;
	DoubleNode* temp = new DoubleNode;
	//DoubleNode* temp->prev = NULL;
	//int min = first->x;

	while (current != NULL)
	{
		min = current;
		inner = current->next;
		

		while (inner != NULL)
		{		
			if (min->x > inner->x)
			{	
				min = inner;
			}
			inner = inner->next;
		}
	
		
		if (min->x < current->x)
		{

			swap(min, current);
		}

		if (min->x < first->x)
		{
			first = min;
		}
		
		//current = current->next;

		
	}
}
*/
