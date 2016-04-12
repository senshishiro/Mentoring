
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
//BigO Analysis:
void SinglyList::addNode(int data)
{
	//create node
	node* n = new node;
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
	else
	{
		head = n;
	}
}

//--------------------------------------------------------
//deleteNode
//BigO Analysis:

void SinglyList::deleteNode(int data)
{
	node* delNode = NULL;
	current = head;
	previous = head;

	//find node
	while (current != NULL && current->x != data)
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL)
	{
		cerr << "error: " << data << " does not exist in the list.\n";
		delete delNode;
	}
	else
	{
		delNode = current;

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
//deleteAll
//BigO Analysis:
void SinglyList::deleteAll()
{
	node* delNode = NULL;
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
//BigO Analysis:
void SinglyList::reverseList()
{
	node* temp = NULL;

	current = head;
	previous = head;
	
	while (current != NULL)
	{
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
//BigO Analysis:

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
//BigO Analysis:
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
	node* n = new node;
	n->x = data;
	n->next = NULL;
	n->prev = NULL;

	if (first != NULL)
	{
		last->next = n;
		n->prev = last;
		last = n;
	}
	else
	{
		first = n;
		last = n;
	}

}
//--------------------------------------------------------
//deleteNode
//BigO: O(N)

void DoublyList::deleteNode(int data)
{
	node* delNode = NULL;
	node* endCurrent = last;
	current = first;
	

	//find node
	while (current != NULL && current->x != data )
	{
		if (endCurrent->x == data)
		{
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

	if (current == NULL)
	{
		cerr << "error: " << data << " does not exist in the list.\n";
		delete delNode;
	}
	else
	{
		delNode = current;

		if (delNode == first)
		{
			first = first->next;
			first->prev = NULL;
		}
		else if (delNode == last)
		{
			last = last->prev;
			last->next = NULL;
		}
		else
		{
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
//BigO: O(N) - One loop that goes through each node and delete the node
void DoublyList::deleteAll()
{
	node* delNode = NULL;
	current = first;

	while (current != NULL)
	{
		delNode = current;
		current = current->next;
		delete delNode;
	}

	//cout << "List has been emptied\n";
	first = NULL;
	current = NULL;
	last = NULL;
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