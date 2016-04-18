
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
	current = NULL;
	previous = NULL;
}

//--------------------------------------------------------
//addNode
//BigO Analysis: O(N) - Goes through the list looking for the last node. Appends node at the end
void SinglyList::addNode(int data)
{
	//create node
	Node* n = new Node;
	n->x = data;
	n->next = NULL;
	

	//if a list already exists
	if (head != NULL)
	{
		current = head;

		//search for the last node of the list
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = n;
	}
	//set to head if a node doesn't exist 
	else
	{
		head = n;
	}
}

//--------------------------------------------------------
//deleteNode
//BigO Analysis: O(N) - Only loops through the linked list once looking for matching value

void SinglyList::deleteNode(int data)
{
	Node* delNode = NULL;
	current = head;
	previous = head;

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
		delete delNode;
	}
	else
	{
		delNode = current;

		//update head if the first node is deleted
		if (delNode == head)
		{
			head = head->next;
		}

		current = current->next;
		previous->next = current;
		delete delNode;

		cout << data << " was deleted from the list.\n";
	}	
}

//--------------------------------------------------------
//deleteAll - Goes through each node and deletes it
//BigO Analysis: O(N) - Only loops through once deleting each node.
void SinglyList::deleteAll()
{
	Node* delNode = NULL;
	current = head;


	while (current != NULL)
	{
		delNode = current;
		current = current->next;
		delete delNode;
	}

	//cout << "List has been emptied\n";
	head = NULL;
	current = NULL;
	previous = NULL;
}

//--------------------------------------------------------
// reverse list
//BigO Analysis: O(N) - Loops through the list rebuilding the list in reverse
void SinglyList::reverseList()
{
	Node* temp = NULL;

	current = head;
	previous = head;
	
	while (current != NULL)
	{
		//Converts the first node into the last
		if (current == head)
		{
			temp = current;
			current = current->next;
			temp->next = NULL;
		}
		else
		{			
				temp = current;
				current = current->next;
				temp->next = previous;				
		}		
		previous = temp;
	}
	
	//if current is at the end of the list, makes the previous node the head
	if (current == NULL)
	{
		head = previous;
	}	
}
//--------------------------------------------------------
//printList
//BigO Analysis:
void SinglyList::printList()
{
	current = head;
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

int SinglyList::size()
{
	int count = 0;
	current = head;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return count; 
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
	current = NULL;
}

//--------------------------------------------------------
//addNode - adds node to the end of the list
//BigO: O(1) - No loops. appends node to last. 
void DoublyList::addNode(int data)
{
	//create node
	Double_Node* n = new Double_Node;
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

}
//--------------------------------------------------------
//deleteNode
//BigO: O(N)

void DoublyList::deleteNode(int data)
{
	Double_Node* delNode = NULL;
	Double_Node* endCurrent = last;
	current = first;
	

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
		delete delNode;
	}
	else
	{
		delNode = current;

		//reaasign first node when it is about to be deleted
		if (delNode == first)
		{
			first = first->next;
			first->prev = NULL;
		}
		//reaasign last node when it is about to be deleted
		else if (delNode == last)
		{
			last = last->prev;
			last->next = NULL;
		}
		else
		{
			//Connect the two nodes adjacent to the deleted node
			current = current->next;
			current->prev = delNode->prev;
			(delNode->prev)->next = current;
		}


		delete delNode;

		cout << data << " was deleted from the list.\n";
	}
}

//--------------------------------------------------------
//deleteAll
//BigO: O(N) - One loop that goes through each node in the list and delete it
void DoublyList::deleteAll()
{
	Double_Node* delNode = NULL;
	current = first;

	while (current != NULL)
	{
		delNode = current;
		current = current->next;
		delete delNode;
	}

	//reset nodes
	first = NULL;
	current = NULL;
	last = NULL;
}

//--------------------------------------------------------
// reverseList
//BigO Analysis: O(N) - Loops through the list swapping the prev and next pointers
void DoublyList::reverseList()
{
	Double_Node* previous = NULL;
	current = first;

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
	current = first;
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
	current = last;
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
//BigO Analysis: O(N) - Loops through linked list counting all the nodes

int DoublyList::size()
{
	int count = 0;
	current = first;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return count;
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