#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// vertex Container



struct Node
{
public:
	string name;
	map<Node*, int> adjList;
	//neighbors
};

class Graph
{
	vector <Node*> vertList;
	vector<pair<Node*,int>> edgeList;
	
	//infinity constant for dijkstra
	const int INF = 999999;

	Node * addVertex(string vertName);

	Node * getVert(string vert);
	//addEdge


	void dfs(Node* n, Node* &dest, map<Node*, bool> &visited);

public:
	void addEdge(string source, string dest, int weight);
	void Graph::shortestPath(string source, string dest);
	void printList();
	void printAdjList(string vertex);
	void pathExist(string source, string dest);

};