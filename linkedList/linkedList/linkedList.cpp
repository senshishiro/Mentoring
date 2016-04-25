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
	int j = dList.getSize();
	cout << "Size of list: " << j << endl;
	dList.deleteNode(10);
	dList.deleteNode(7);
	dList.reverseList();
	dList.printList();
	dList.printListReverse();
	cout << "-------------------------------------------\n";
	//dList.sort();
	j = dList.getSize();
	cout << "Size of list: " << j << endl;
	cout << "List Deleted\n";
	dList.deleteAll();
	dList.printList();
	j = dList.getSize();
	cout << "Size of list: " << j << endl;

	
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
	int k = list.getSize();
	cout << "Size of list: " << k << endl;
	list.deleteNode(0);
	list.deleteNode(22);
	list.printList();
	list.reverseList();
	list.printList();
	k = list.getSize();
	cout << "Size of list: " << k << endl;
	list.deleteAll();
	list.printList();


    return 0;
}

