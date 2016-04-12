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
	
	dList.addNode(1);
	dList.addNode(3);
	dList.addNode(5);
	dList.addNode(7);
	dList.addNode(9);
	dList.addNode(11);


	dList.deleteNode(11);
	dList.printList();
	dList.printListReverse();
	dList.deleteAll();
	dList.printList();
	/*
	list.addNode(3);
	list.addNode(5);
	list.addNode(7);

	list.printList();
	//int k = list.size();
	//cout << "Size of list: " << k << endl;

	list.deleteNode(7);
	//list.deleteAll();
	
	list.addNode(9);
	list.printList();
	list.reverseList();
	list.printList();
	*/
    return 0;
}

