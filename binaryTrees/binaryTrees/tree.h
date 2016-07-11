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

	Node * BinaryTree::insertNode(Node * root, int value);
	Node * searchNode(Node * n, int value);
public:
	Node * root;
	BinaryTree();
	//search
	void search(int value);
	//add
	Node * createNode(Node * temp, int value);
	void addNode(int value);

	//delete
	void deleteNode(int value);
	//print
	void printTree(Node * node);
	//void printNode();

	//rebalance
};