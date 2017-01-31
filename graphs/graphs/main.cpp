// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graphs.h"


int main()
{
	Graph test;

	test.addEdge("A", "B", 1);
	test.addEdge("B", "D", 5);
	test.addEdge("B", "C", 3);
	test.addEdge("D", "B", 1);
	test.addEdge("B", "A", 2);
	test.addEdge("C", "D", 4);

	test.printList();

	cout << endl;

	test.printAdjList("B");
    return 0;
}

