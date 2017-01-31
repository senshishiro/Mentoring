#include "stdafx.h"
#include "graphs.h"


//addVertex
Node * Graph::addVertex(string vertName)
{
	Node* n = new Node;
	n->name = vertName;

	return n;
}


Node * Graph::getVert(string vertName)
{
	if (vertList.size() == 0)
	{
		return NULL;
	}
	else
	{
		for (size_t i = 0; i < vertList.size(); i++)
		{
			if (vertList[i]->name == vertName)
			{
				return vertList[i];
			}
		}
		return NULL;
	}
}

//addEdge
void Graph::addEdge(string source, string dest, int weight)
{
	//check if verts exist
	Node * sourceNode = NULL;
	Node * destNode = NULL;

	sourceNode = getVert(source);
	destNode = getVert(dest);

	if (sourceNode == NULL)
	{	
		sourceNode = addVertex(source);
		vertList.push_back(sourceNode);
	}

	if (destNode == NULL)
	{
		destNode = addVertex(dest);
		vertList.push_back(destNode);
	}
	//add to node's adj list
	sourceNode->adjList[destNode] = weight;
	//cout << sourceNode->name << " " << destNode->name << " " << sourceNode->adjList[destNode] << endl;
}

//printEdgeList

void Graph::dijkstra(string source, string dest)
{
	//initialize
	map<Node*, int> unvisted;
	map<Node*, int> visted;
	Node * sourceNode;

	for (int i = 0; i < vertList.size(); i++)
	{
		//grab pointer for source node
		if (vertList[i]->name == source)
		{
			sourceNode = vertList[i];
		}
		else
		{
			//load unvisted with pointers and weights
			unvisted[vertList[i]] = INF;
		}
	}
	
	//starting vertices
	//remove source node
	// set vertices weight to inf

	//visted vertices
	//add source node. set weight to 0

	// loop until current node == dest node
	//from source node loop through all adj verts.
	// update weight on adj verts if they're lower than inf
	// find one with lowest weight
	// add lowest weight vert to visted
	// remove from source

}


void Graph::printList()
{
	cout << "edges:\n";
	for (int i = 0; i < vertList.size(); i++)
	{
		map<Node*, int> neighbors;
		neighbors = vertList[i]->adjList;

		for (auto key = neighbors.cbegin(); key != neighbors.cend(); key++)
		{
			cout << vertList[i]->name << " " << (key->first)->name << " " << (key->second) << endl;
		}
	}
}

//printAdljList

void Graph::printAdjList(string vertex)
{

	Node * source = getVert(vertex);

	map<Node*, int> neighbors;
	neighbors = source->adjList;

	for (auto key = neighbors.cbegin(); key != neighbors.cend(); key++)
	{
	cout << source->name << " " << (key->first)->name << " " << (key->second) << endl;
	}

}