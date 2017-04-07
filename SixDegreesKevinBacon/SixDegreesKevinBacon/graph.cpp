#include "stdafx.h"
#include "graph.h"



// create graph from text file
void Graph::createGraph()
{
	int count = 0;
	string line;
	ifstream file(TEXTPATH);

	if (file.is_open())
	{
		vector<string> info;

		while (getline(file, line))
		{
			stringstream ss(line);
			string temp;

			while (getline(ss, temp, ';'))
			{
				info.push_back(temp);
			}

			createMovieEdges(info);
			info.clear();
			count++;
		}
	}
}


Node * Graph::addVertex(string vertName)
{
	Node* n = new Node;
	n->name = vertName;
	return n;
}


Node * Graph::addActor(string name)
{
	Node* n;
	n = addVertex(name);
	n->isMovie = false;
	actorList.push_back(n);
	return n;
}


Node * Graph::addMovie(string name)
{
	Node* n;
	n = addVertex(name);
	n->isMovie = true;
	movieList.push_back(n);
	return n;
}


// Look for vert in the vert list
Node * Graph::getVert(string vertName, vector<Node*> & vertList)
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

Node * Graph::findActor(string name)
{
	return getVert(name, actorList);
}


Node * Graph::findMovie(string name)
{
	return getVert(name, movieList);
}

// returns a combine list of actors and movies used for creating the visit map
vector<Node*> Graph::getVisitList()
{
	if (visitList.empty())
	{
		visitList.insert(visitList.end(), actorList.begin(), actorList.end());
		visitList.insert(visitList.end(), movieList.begin(), movieList.end());
	}
	else
	{
		return visitList;
	}
}

//addEdge
void Graph::addEdge(Node* sourceNode, Node* destNode, int weight, map<Node*, vector<pair<Node*,int>>> &list)
{
	list[sourceNode].push_back(make_pair(destNode, weight));
}


// createMovieEdges
// Takes the vector from txt file, and creates nodes/edges.
void Graph::createMovieEdges(vector<string> data)
{
	// set source to film title
	string source = data[0];

	// remove movie title from the vector
	data.erase(data.begin());

	Node* sourceNode = findMovie(source);

	if (sourceNode == NULL)
	{
		sourceNode = addMovie(source);
	}

	for (const auto& dest : data)
	{
		Node* destNode = findActor(dest);

		if (destNode == NULL)
		{
			destNode = addActor(dest);
		}

		// Add edges to cast list and film list
		addEdge(sourceNode, destNode, BACON_WEIGHT, castEdgeList);
		addEdge(destNode, sourceNode, BACON_WEIGHT, filmEdgeList);
	}
}

// pathExist
// Checks if a path exists between two nodes
bool Graph::pathExist(Path path)
{
	Node* sourceNode = path.source;
	Node* destNode = path.dest;
	map<Node*, bool> visited;

	// create a combine visited list of movies and actors
	vector<Node*> temp = getVisitList();
	
	if (sourceNode != NULL && destNode != NULL)
	{
		// populate visited map with all movies and actors
		for (int i = 0; i < temp.size(); i++)
		{
			visited[temp[i]] = false;
		}

		// recursively searches through the graph looking for the dest node.
		if (dfs(sourceNode, destNode, visited))
		{
			//cout << "A path exists between " << sourceNode->name << " and " << destNode->name << endl;
			return true;
		}
		else
		{
			//cout << "A path does not exists between " << sourceNode->name << " and " << destNode->isMovie << endl;
			return false;
		}
	}
	else
	{
		return false;
	}
}

// dfs
// recursively searches through each node in the graph from source to dest
bool Graph::dfs(Node* n, Node* &dest, map<Node*, bool> &visited)
{
	visited[n] = true;
	vector<pair<Node*, int>> AdjList;

	if (n->isMovie)
	{
		AdjList = castEdgeList[n];
	}
	else
	{
		AdjList = filmEdgeList[n];
	}

	if (n->name == dest->name)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < AdjList.size(); i++)
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


// shortestPath
void Graph::shortestPath(Path &path)
{
	Node* sourceNode = path.source;
	Node* destNode = path.dest;
	map<Node*, Node*> parent;

	map<Node*, bool> mapVisited;
	map<Node*, int> mapVertWeight;
	priority_queue<pair<Node*, int>, vector< pair<Node*, int> >, Comparator> queue;
	vector<Node*> temp = getVisitList();

	//initialize maps and nodes
	for (int i = 0; i < temp.size(); i++)
	{
		//load unvisted with pointers and weights
		mapVertWeight[temp[i]] = INF;
		mapVisited[temp[i]] = false;
	}

	// add sourceNode to queue
	queue.push(make_pair(sourceNode, 0));
	mapVertWeight[sourceNode] = 0;
	parent[sourceNode] = NULL;

	// loops though the queue
	while (!queue.empty())
	{
		Node* currNode = queue.top().first;
		int currCost = queue.top().second;
		vector<pair<Node*, int>> AdjList;

		if (currNode->isMovie)
		{
			AdjList = castEdgeList[currNode];
		}
		else
		{
			AdjList = filmEdgeList[currNode];
		}

		// remove node from queue
		queue.pop();

		// check if node has been visited
		if (mapVisited[currNode] == false)
		{
			mapVisited[currNode] = true;

			// cycle through all adj nodes
			for (const auto& x : AdjList)
			{
				int adjWeight = x.second;

				if (!mapVisited[x.first] && mapVertWeight[x.first] > mapVertWeight[currNode] + adjWeight)
				{
					// update parent
					parent[x.first] = currNode;

					// update map with the total weight 
					mapVertWeight[x.first] = mapVertWeight[currNode] + adjWeight;

					// add node to queue
					queue.push(make_pair(x.first, mapVertWeight[x.first]));
				}
			}
		}
	}

	// update path weight
	path.fullPath = parent;
	path.weight = mapVertWeight[destNode];
}


//printEdges
void Graph::printEdges(map<Node*, vector<Node*>> & edgeList)
{
	for (const auto& n : edgeList)
	{
		cout << "movie: " << n.first->name << endl;
		cout << "cast:\n";
		for (int i = 0; i < n.second.size(); ++i)
		{
			cout << n.second[i]->name<<endl;
		}
	}
}

