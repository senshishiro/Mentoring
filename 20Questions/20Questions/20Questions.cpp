// 20Questions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "qtree.h"
#include "controller.h"


using namespace std;

int main()
{

	QTree test;

	test.importQuestions();

	test.treeTraversal(test.root);
	//test.printTree(test.root);
	/*
	for (int i = 0; i < qStorage.size(); i++)
	{
		cout << qStorage[i].type << " " << qStorage[i].data << endl;
	}*/
    return 0;
}

