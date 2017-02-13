#include "stdafx.h"
#include "controller.h"

void GraphController::printEdges()
{
	gController.printEdges();
}

// create graph from text file
void GraphController::textToGraph()
{
	int count = 0;
	string line;
	ifstream file(TEXTPATH);

	if (file.is_open())
	{
		string source, dest, weight;
		//int weight;

		while (getline(file, line))
		{
			stringstream ss(line);
			
			getline(ss, source, ' ');
			getline(ss, dest, ' ');
			getline(ss, weight);

			gController.addEdge(source, dest, stoi(weight));
			count++;
		}
	}
	
	cout << count << " number of edges added.\n";
}
	//findshortpath
void GraphController::findShortPath(string source, string dest)
{
	// check if path exists
	if (gController.pathExist(source, dest))
	{
		// search for shortest path
		gController.findShortestPath(source, dest);
	}
}