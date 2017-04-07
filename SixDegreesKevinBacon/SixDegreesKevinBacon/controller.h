#pragma once

#include "graph.h"
#include "inputs.h"

class Controller
{
	Graph graph;
	Inputs input;

	const string BACON = "Kevin Bacon";

	void Controller::drawLine();
	Path findBaconPath(string source, string dest);

	void printPath(Node* n, Path &path, Node* &prev);
	void printBaconPath(Path &path);
	void printBaconNumResults(Path &baconPath);

public:
	void sixDegreesGame();
};

