#include "stdafx.h"
#include "controller.h"

/*
void GraphController::printFilmInfo()
{
	graph.printEdges(graph.castEdgeList);
}

void GraphController::printFilmography()
{
	graph.printEdges(graph.filmEdgeList);
}*/


// draws line
void Controller::drawLine()
{
	cout << "-------------------------------------\n";
}


//findshortpath
Path Controller::findBaconPath(string source, string dest)
{
	Path baconPath;

	baconPath.source = graph.findActor(source);
	baconPath.dest = graph.findActor(dest);
	
	// check if path exists
	if (baconPath.source != NULL)
	{
		if (graph.pathExist(baconPath))
		{
			// search for shortest path
			graph.shortestPath(baconPath);	
		}
	}
	else
	{
		cout << "A path does not exists between " << source << " and " << dest << " or "
			 << source << " does not exists in the list\n";
	}	
	return baconPath;
}


void Controller::printBaconNumResults(Path &baconPath)
{
	// divide the weight by two to get the actual bacon number
	int baconNum = baconPath.weight / 2;

	if (baconNum != 0 && baconNum <= 6)
	{
		cout << baconPath.source->name << "'s Bacon number is " << baconNum << ".\n";
	}
	else if (baconNum != graph.INF && baconNum >= 7)
	{
		cout << baconPath.source->name << "'s Bacon Number is greater than 6.\n";
	}
	else if (baconNum == 0)
	{
		cout << "Kevin Bacon's Bacon number is " << baconNum << ".\n";
	}
	else
	{
		cout << "Path from " << baconPath.source->name << " to " << baconPath.dest->name << " does not exist.\n";
	}
}


// printPath
// print actors and movie names
void Controller::printPath(Node* n, Path &path, Node* &prev)
{
	if (n == path.source)
	{
		cout << n->name;
		prev = n;
	}
	else
	{
		printPath(path.fullPath[n], path, prev);

		// base
		if (n->isMovie && prev == path.source)
		{
			cout << " was in " << n->name << " with ";
		}
		else if (n->isMovie)
		{
			cout << prev->name << " was in " << n->name << " with ";
		}
		else
			cout << n->name << endl;

		// update prev if the node is an actor
		if (!n->isMovie)
			prev = n;
	}
}

void Controller::printBaconPath(Path &path)
{
	Node* temp = NULL;
	printPath(path.dest, path, temp);
}

// main game loop
void Controller::sixDegreesGame()
{
	string playerInput;
	bool bExit = true;
	Path path;

	graph.createGraph();

	drawLine();
	cout << "Six Degrees of Bacon\n";
	drawLine();

	do
	{
		cout << "Please enter an actor/actress: ";
		playerInput = input.getActor();
		
		path = findBaconPath(playerInput, BACON);

		if (path.source != NULL)
		{
			cout << endl;
			if (playerInput != "Kevin Bacon")
			{
				printBaconPath(path);
			}
			printBaconNumResults(path);
		}

		drawLine();
		cout << "Would you like to enter another actor/actress?\n";
		bExit = input.getInput();

	} while (bExit);

	cout << "Thanks for Playing.\n";
}