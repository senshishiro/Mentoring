#pragma once

#include <iostream>

using namespace std; 

//==========================================================================
//Binary Tree Node
//==========================================================================
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
	//add
	Node * insertNode(Node * root, int value);
	//delete
	Node * deleteNode(Node * root, int value);
	//search
	bool searchNode(Node * n, int value);
	//create node
	Node * createNode(Node * temp, int value);
	//find successor
	Node * successorNode(Node * root);
	//find max
	int max(int a, int b);
	// calculate height
	int height(Node * node);
	
	//rebalancing and Rotations
	void rebalance(Node * n);
	Node * rotateRight(Node * pivot);
	Node * rotateLeft(Node * pivot);
	Node * rotateRightLeft(Node * pivot);
	Node * rotateLeftRight(Node * pivot);
public:
	Node * root;
	BinaryTree();
	
	//search
	void search(int value);
	
	//add
	void addNode(int value);

	//delete
	void removeNode(int value);
	
	//print
	void printTree(Node * node);
};
