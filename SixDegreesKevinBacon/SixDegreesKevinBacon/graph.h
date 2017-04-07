#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

struct Node
{
public:
	string name;
	bool isMovie;
};

struct Path
{
public:
	Node* source;
	Node* dest;
	int weight;
	map<Node*, Node*> fullPath;
};

class Comparator
{
public:
	bool operator ()(pair<Node*, int> &p1, pair<Node*, int> &p2)
	{
		return p1.second > p2.second;
	}
};

class Graph
{
	
	const int BACON_WEIGHT = 1;
	const string TEXTPATH = "movies.txt";

	vector <Node*> actorList;
	vector <Node*> movieList;

	// a combined list of actor and movies used for creating a visted map
	vector <Node*> visitList;

	map <Node*, vector<pair<Node*, int>>> castEdgeList;
	map <Node*, vector<pair<Node*, int>>> filmEdgeList;

	Node * addVertex(string vertName);
	Node * getVert(string vert, vector<Node*> & vertList);
	vector<Node*> getVisitList();
	void addEdge(Node* sourceNode, Node* destNode, int weight, map<Node*, vector<pair<Node*, int>>> &list);

	bool dfs(Node* n, Node* &dest, map<Node*, bool> &visited);
	

public:
	const int INF = 999;

	void Graph::createGraph();

	Node * addActor(string name);
	Node * addMovie(string name);
	Node * findMovie(string name);
	Node * findActor(string name);

	void shortestPath(Path &path);
	
	void createMovieEdges(vector<string> data);
	bool pathExist(Path path);

	void printEdges(map<Node*, vector<Node*>> & edgeList);
	//void printPath(Node* n, Node* source, map<Node*, Node*> &parent, Node* &prev);
};
