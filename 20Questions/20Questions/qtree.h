#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "inputs.h"

using namespace std;

struct Node
{
	string data;
	bool isQuestion;
	//no
	Node* left;
	//yes
	Node* right; 
};

//==========================================================================
//Question Tree
//==========================================================================

class QTree
{
private:
	// value for if the tree has been modified
	bool bModified;

	Node* createNode(Node * n, string data, bool type);

	// recursive function for navigating the tree
	Node* treeTraversal(Node * node, Node * previous, bool &bWin);

	//void treeSize();
	//unsigned int treeNodes(Node * n);

public:
	Node* root;
	Node* lastAnswer;
	Node* previousToLastAnswer;

	// constructor
	QTree();

	// returns bModified
	bool isModified();

	// updates bModified
	void updateModified(bool value);

	// add nodes to the tree
	void insertNode(Node * &n, vector<Qset> &questions, unsigned int &count);

	// Navigate through tree with y/n responses
	void askQuestion(Node * node, bool &bWin);

	// adds/swaps new answer and questions. 
	void addNewAnswer(NewAnswer answer, Node * compAnswer, Node* previous);

	//void printTree(Node * node);
	
};