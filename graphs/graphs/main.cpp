// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "controller.h"


int main()
{
	GraphController test;

	/*
	test.addEdge("A", "B", 4);
	test.addEdge("A", "C", 2);
	test.addEdge("C", "B", 1);
	test.addEdge("B", "D", 5);
	test.addEdge("C", "E", 10);
	test.addEdge("C", "D", 8);
	test.addEdge("D", "E", 20);
	test.addEdge("D", "Z", 6);
	test.addEdge("E", "Z", 3);
	*/

	//test.printList();
	test.textToGraph();
	test.printEdges();
	cout << endl;
	test.findShortPath("A", "D");

	return 0;
}

