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
	test.printEdges();
	cout << endl;

	//test.printAdjList("B");

	if (test.pathExist("A", "D"))
	{
		test.findShortestPath("A", "D");
	}

	//cout << endl;
	//test.pathExist("A", "D");
    
	/*while (!pq.empty())
	{
		pair<string, int> n = pq.top();

		cout << n.first << " " << n.second << endl;

		pq.pop();

	}*/
	return 0;
}

