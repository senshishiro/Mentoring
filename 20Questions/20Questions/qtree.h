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
	
	// loads text file into a vector
	vector<Qset> convertQuestionText();

	Node* insertNode(Node * &n, vector<Qset> &questions, unsigned int &count);
	Node* createNode(Node * n, string data, bool type);
	
	//input
	string toLowercase(string str);
	bool getInput();
	string getData();
	void addNewAnswer(Node * compAnswer, Node* previous);

	// recursive function for navigating the tree
	Node* askQuestion(Node * node, Node * previous);

	// recursive function for dumping info from the tree to text file
	void printToTxt(fstream &stream, Node * node);

	//void treeSize();
	//unsigned int treeNodes(Node * n);

public:
	Node* root;
	bool bModified;
	// constructor
	QTree();

	//play again
	bool playAgain();

	//Load questions and build tree
	void importQuestions();

	// Navigate through tree with y/n responses
	void treeTraversal(Node * node);

	// update text file
	void updateTxt();

	//void printTree(Node * node);
	
};