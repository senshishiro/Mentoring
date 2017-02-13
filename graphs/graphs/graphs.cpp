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


int Graph::getWeight(Node* n)
{
	for (int i = 0; i < edgeList[n].size(); ++i)
	{
		if (edgeList[n][i].first == n)
		{
			return edgeList[n][i].second;
		}
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
	//sourceNode->adjList[destNode] = weight;
	edgeList[sourceNode].push_back(make_pair(destNode,weight));
	//cout << sourceNode->name << " " << destNode->name << " " << sourceNode->adjList[destNode] << endl;
}


// pathExist
// Checks if a path exists between two nodes

bool Graph::pathExist(string source, string dest)
{
	Node* sourceNode = getVert(source);
	Node* destNode = getVert(dest);
	map<Node*, bool> visited;
	
	if (sourceNode != NULL && destNode != NULL)
	{
		// set all values in the map to false
		for (int i = 0; i < vertList.size(); i++)
		{
			//load unvisted with pointers and weights
			visited[vertList[i]] = false;
		}

		// recursively searches through the graph looking for the dest node.
		if (dfs(sourceNode, destNode, visited))
		{
			cout << "A path exists between " << source << " and " << dest << endl;
			return true;
		}
		else
		{
			cout << "A path does not exists between " << source << " and " << dest << endl;
			return false;
		}
	}
	else
	{
		if (sourceNode == NULL)
		{
			cout << "Source Node does not exists.\n";
		}

		if (destNode == NULL)
		{
			cout << "Destination Node does not exist.\n";
		}
		return false;
	}


	
}

// dfs
// recursively searches through each node in the graph from source to dest
bool Graph::dfs(Node* n, Node* &dest, map<Node*, bool> &visited)
{
	visited[n] = true;
	vector<pair<Node*, int>> AdjList = edgeList[n];

	if (n->name == dest->name)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < AdjList.size(); ++i)
		{
			// check if node has been visited
			if (!visited[AdjList[i].first])
			{
				if (dfs(AdjList[i].first, dest, visited))
				{
					return true;
				}
			}
		}
		return false;
	}
}

void Graph::findShortestPath(string source, string dest)
{
	Node* sourceNode = getVert(source);
	Node* destNode = getVert(dest);
	map<Node*, int> mapVertWeight;
	
	//vector<Node*> results;
	shortestPath(sourceNode, destNode, mapVertWeight);

	// Checks if the last node is still set at INF
	if (mapVertWeight[destNode] != INF)
	{
		cout << "Shortest Path Weight between " << source << " and " << dest << " is " << mapVertWeight[destNode] << endl;
	
		/*
		//cout << "size: " << results.size() << endl;
		for (int i = 0; i < results.size(); i++)
		{
			cout << results[i]->name;
			//cout << edgeList[].
			if (i < results.size()-1)
				cout << "->";
			else
				cout << endl;
		}*/
	}
	else
	{
		cout << "Path from " << source << " to " << dest << " does not exist.\n";
	}
}


// shortestPath
void Graph::shortestPath(Node* &sourceNode, Node* &destNode, map<Node*, int> &mapVertWeight)
{
	map<Node*, bool> mapVisited;
	priority_queue<pair<Node*, int>, vector< pair<Node*, int> >, Comparator> queue;
	vector<Node*> prev;

	//initialize maps and nodes
	for (int i = 0; i < vertList.size(); i++)
	{
		//load unvisted with pointers and weights
		mapVertWeight[vertList[i]] = INF;
		mapVisited[vertList[i]] = false;
	}

	// add sourceNode to queue
	queue.push(make_pair(sourceNode, 0));
	mapVertWeight[sourceNode] = 0;

	// loops though the queue
	while (!queue.empty())
	{
		Node* currNode = queue.top().first;
		int currCost = queue.top().second;
		vector<pair<Node*, int>> AdjList = edgeList[currNode];

		//cout << currNode->name << " " << currCost << endl;
		// remove node from queue
		queue.pop();
		
		// check if node has been visited
		if (mapVisited[currNode] == false)
		{
			mapVisited[currNode] = true;
			//cout << currNode->name << " has been visited\n";

			//cycle through all adj nodes
			for (const auto& x : AdjList)
			{
				int adjWeight = x.second;
						
				if(!mapVisited[x.first] && mapVertWeight[x.first] > mapVertWeight[currNode]+adjWeight)
				{
					// update map with the total weight 
					mapVertWeight[x.first] = mapVertWeight[currNode] + adjWeight;
					//cout << " cost " << mapVertWeight[x.first] << endl;

					queue.push(make_pair(x.first, mapVertWeight[x.first]));
				}
			}
		}
	}
	
	//cout << "queue is empty\n";
	//return prev;

}


//printEdges
void Graph::printEdges()
{
	cout << "edges:\n";
	for (const auto& n : edgeList)
	{
		for (int i = 0; i < n.second.size(); ++i)
		{
			cout << n.first->name << " " << (n.second[i].first)->name << " : " << n.second[i].second << endl;
		}
	}
}