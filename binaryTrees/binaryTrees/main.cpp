// binaryTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tree.h"
#include <vector>

int main()
{
	BinaryTree tree;

	vector<int> testData = {5, 3, 10, 7, 8, 1};

	for (int i = 0; i < testData.size(); i++)
	{
		cout << "-------------------------------\n";
		cout << "adding: " << testData[i] << endl;
		tree.addNode(testData[i]);
		cout << "-------------------------------\n";
	}
	
	/*
	tree.addNode(5);
	tree.addNode(3);
	tree.addNode(10);
	tree.addNode(7);
	tree.addNode(8);
	tree.addNode(1);
	*/

	tree.printTree(tree.root);
	cout << endl;
	tree.search(8);
	cout << endl;
	tree.deleteNode(8);
	tree.printTree(tree.root);
	cout << endl;
    return 0;
}

