// linkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "list.h"
#include <iostream>


using namespace std; 

int main()
{
	SinglyList list;
	DoublyList dList;
	cout << "-------------------------------------------\n";
	cout << "Doubly Linked List:\n";
	cout << "-------------------------------------------\n";

	dList.addNode(1);
	dList.addNode(3);
	dList.addNode(5);
	dList.addNode(7);
	dList.addNode(9);
	dList.addNode(11);
	dList.addNode(13);
	dList.printList();

	dList.deleteNode(10);
	dList.deleteNode(7);
	dList.reverseList();
	dList.printList();
	dList.printListReverse();
	int j = dList.size();
	cout << "Size of list: " << j << endl;
	cout << "List Deleted\n";
	dList.deleteAll();
	dList.printList();
	
	//-------------------------------------------
	cout << "-------------------------------------------\n";
	cout << "Singly Linked List:\n";
	cout << "-------------------------------------------\n";

	list.addNode(0);
	list.addNode(2);
	list.addNode(4);
	list.addNode(3);
	list.addNode(7);
	list.addNode(1);
	list.addNode(6);
	list.addNode(8);
	list.addNode(10);
	list.printList();
	list.deleteNode(7);
	list.deleteNode(22);
	list.printList();
	list.reverseList();
	list.printList();
	int k = list.size();
	cout << "Size of list: " << k << endl;
	list.deleteAll();
	list.printList();
    return 0;
}

