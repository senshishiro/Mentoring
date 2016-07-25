#pragma once

#include <iostream>

using namespace std; 


//node
struct Node
{
	int data;
	int height;
	Node* left;
	Node* right;
	Node* parent;
	
};

//==========================================================================
//Binary Tree
//==========================================================================
class BinaryTree
{
private:

	Node * insertNode(Node * root, int value);
	Node * deleteNode(Node * root, int value);
	bool searchNode(Node * n, int value);

	//findSuccessor
	Node * successorNode(Node * root);

public:
	Node * root;
	BinaryTree();
	//search
	void search(int value);
	//add
	Node * createNode(Node * temp, int value);
	void addNode(int value);

	//delete
	void removeNode(int value);
	//print
	void printTree(Node * node);
	int max(int a, int b);
	int height(Node * node);


	//rebalance
	void rebalance(Node * n);
	Node * rotateRight(Node * pivot);
	Node * rotateLeft(Node * pivot);
	Node * rotateRightLeft(Node * pivot);
	Node * rotateLeftRight(Node * pivot);


};