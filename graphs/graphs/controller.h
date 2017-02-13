#pragma once
#include <fstream>
#include <sstream>
#include "graphs.h"


class GraphController
{
	Graph gController;
	const string TEXTPATH = "edges.txt";
	
	//void textToGraph();


public:
	void textToGraph();
	void printEdges();
	void findShortPath(string source, string dest);
};


