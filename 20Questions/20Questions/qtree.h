#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Qset
{
	string type;
	string data;
};

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
	// adding nodes
	vector<Qset> convertQuestionText();
	Node* insertNode(Node * &n, vector<Qset> questions, int &count);
	Node* createNode(Node * n, string data, bool type);
	
	//input
	Node* askQuestion(Node * node);
	bool getInput();
	bool playAgain();
	string toLowercase(string str);

public:
	Node* root;

	// constructor
	QTree();

	//add
	void importQuestions();
	//void printTree(Node * node);

	void treeTraversal(Node * node);

};