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

void Graph::pathExist(string source, string dest)
{
	Node* sourceNode = getVert(source);
	Node* destNode = getVert(dest);
	map<Node*, bool> visited;
	
	// set all values in the map to false
	for (int i = 0; i < vertList.size(); i++)
	{
		//load unvisted with pointers and weights
		visited[vertList[i]] = false;
	}

	// recursively searches through the graph looking for the dest node.
	if(dfs(sourceNode, destNode, visited))
	{
		cout << "A path exists between " << source << " and " << dest << endl;
	}
	else
	{
		cout << "A path does not exists between " << source << " and " << dest << endl;
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
	vector<Node*> results;

	results = shortestPath(sourceNode, destNode, mapVertWeight);

	// Checks if the last node is still set at INF
	if (mapVertWeight[destNode] != INF)
	{
		cout << "Shortest Path Weight between " << source << " and " << dest << " is " << mapVertWeight[destNode] << endl;
	
		//cout << "size: " << results.size() << endl;
		for (int i = 0; i < results.size(); i++)
		{
			cout << results[i]->name;
			//cout << edgeList[].
			if (i < results.size()-1)
				cout << "->";
			else
				cout << endl;
		}
	}
	else
	{
		cout << "Path from " << source << " to " << dest << " does not exist.\n";
	}
}

// shortestPath
vector<Node*> Graph::shortestPath(Node* &sourceNode, Node* &destNode, map<Node*, int> &mapVertWeight)
{
	//initialize
	
	map<Node*, bool> mapVisited;
	vector<pair<Node*, int>> queue;
	vector<Node*> prev;

	//results.push_back(sourceNode);

	//initialize maps and nodes
	for (int i = 0; i < vertList.size(); i++)
	{
		//load unvisted with pointers and weights
		mapVertWeight[vertList[i]] = INF;
		mapVisited[vertList[i]] = false;
	}

	// add sourceNode to queue
	queue.push_back(make_pair(sourceNode, 0));
	mapVertWeight[sourceNode] = 0;

	// loops though the queue
	while (!queue.empty())
	{
		Node* currNode = queue.front().first;
		int currWeight = queue.front().second;
		Node* minNode = NULL;
		int minWeight = INF;
		vector<pair<Node*, int>> AdjList = edgeList[currNode];

		// remove node from queue
		queue.pop_back();
		
		//cycle through all adj nodes
		for (const auto& x : AdjList)
		{
			int adjWeight = x.second;
			//int tempDist = currWeight + adjWeight;

			// check if adj node has been visited
			if (mapVisited[x.first] == false)
			{
				//mapVertWeight[x.first] = tempDist;

				// keeps track of the node with the smallest weight

				//if (tempDist < minWeight)
				if(mapVertWeight[x.first] > mapVertWeight[currNode]+adjWeight)
				{
					//minNode = x.first;
					//minWeight = tempDist;		

					// update map with the total weight for each node
					mapVertWeight[x.first] = mapVertWeight[currNode] + adjWeight;

					if (mapVertWeight[x.first] < minWeight)
					{
						minNode = x.first;
						minWeight = mapVertWeight[x.first];
					  //mapVisited[currNode] = true;
				    	//	prev.push_back
						if (minNode == destNode)
							break;

					}

					//mapVertWeight[x.first] = mapVertWeight[currNode] + adjWeight;
					//queue.push_back(make_pair(minNode, mapVertWeight[minNode]));
				}
			}
		}

		// if a min node still exists continue looking at adjNodes
		
		if (minNode != NULL)
		{
			//cout << edgeList[currNode][0].second << " " << minWeight << endl;
			mapVisited[currNode] = true;
			prev.push_back(currNode);
			queue.push_back(make_pair(minNode, mapVertWeight[minNode]));
		}
		else if (currNode == destNode)
		{
			prev.push_back(currNode);
		}
	}
	
	return prev;

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