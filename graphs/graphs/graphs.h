#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// vertex Container



struct Node
{
public:
	string name;
	//map<Node*, int> adjList;
	//neighbors
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
	vector <Node*> vertList;
	map <Node*, vector<pair<Node*,int>>> edgeList;
	
	//infinity constant for dijkstra
	const int INF = 999999;

	Node * addVertex(string vertName);
	Node * getVert(string vert);

	int getWeight(Node* n);
	bool dfs(Node* n, Node* &dest, map<Node*, bool> &visited);
	void shortestPath(Node* &source, Node* &dest, map<Node*, int> &mapWeight);

public:
	void addEdge(string source, string dest, int weight);
	void findShortestPath(string source, string dest);
	bool pathExist(string source, string dest);
	void printEdges();
};