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


// DFS
// Searches 


void Graph::pathExist(string source, string dest)
{
	Node* temp = NULL;
	Node* sourceNode = NULL;
	Node* destNode = NULL;
	map<Node*, bool> visited;

	for (int i = 0; i < vertList.size(); i++)
	{
		//load unvisted with pointers and weights
		visited[vertList[i]] = false;

		if (vertList[i]->name == source)
		{
			sourceNode = vertList[i];
		}

		if (vertList[i]->name == dest)
		{
			destNode = vertList[i];
		}
	}

	dfs(sourceNode, destNode, visited);
	
}

void Graph::dfs(Node* n, Node* &dest, map<Node*, bool> &visited)
{
	visited[n] = true;
	cout << n->name << endl;
	if (n->name == dest->name)
	{
		cout << "Path Exists\n";
	}
	else
	{
		for (const auto& x : n->adjList)
		{
			if (!visited[x.first])
			{
				dfs(x.first, dest, visited);
			}
		}
	}
}


// shortestPath
void Graph::shortestPath(string source, string dest)
{
	//initialize
	map<Node*, int> vertices;
	map<Node*, bool> visited;
	vector<pair<Node*, int>> queue;

	Node * sourceNode = NULL;
	Node * destNode = NULL;

	//initialize maps and nodes
	for (int i = 0; i < vertList.size(); i++)
	{
		//load unvisted with pointers and weights
		vertices[vertList[i]] = INF;
		visited[vertList[i]] = false;

		if (vertList[i]->name == source)
		{
			sourceNode = vertList[i];
		}

		if (vertList[i]->name == dest)
		{
			destNode = vertList[i];
		}
	}

	queue.push_back(make_pair(sourceNode, 0));

	// loops though the queue
	while (!queue.empty())
	{
		Node* curr = queue.front().first;
		int currWeight = queue.front().second;

		Node* minNode = NULL;
		queue.pop_back();

		int minWeight = INF;

		//cout << "current node: " << curr->name << endl;

		//cycle through all adj nodes
		for (const auto& x : curr->adjList)
		{
			int adjWeight = x.second;
			int tempDist = currWeight + adjWeight;

			// check if 
			if (visited[x.first] == false)
			{
				vertices[x.first] = tempDist;
				//cout << "node: " << curr->name << " to adj node: " << x.first->name << " weight: " << tempDist << endl;
				//cout << "min weight " << minWeight << endl;

				if (tempDist < minWeight)
				{
					//cout << "min node is " << x.first->name << " with weight: " << tempDist << endl;
					minNode = x.first;
					minWeight = tempDist;				
					vertices[x.first] = tempDist;
					//cout << "min weight " << minWeight << endl;
					//cout << "total weight at node " << x.first->name <<" is "<< vertices[x.first] << endl;			
				}
			}
			else
			{
				cout << x.first->name << " has been visited\n";
			}
		}


		if (minNode != NULL)
		{
			visited[curr] = true;
			cout << vertices[minNode] << endl;
			queue.push_back(make_pair(minNode, vertices[minNode]));
		}
	}

	if (vertices[destNode] != INF)
	{
		cout << "Shortest Weight Path between " << source << " and " << dest << " is " << vertices[destNode] << endl;
	}
	else
	{
		cout << "Path from " << source << " to " << dest << " does not exist.\n";
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


//printEdgeList
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