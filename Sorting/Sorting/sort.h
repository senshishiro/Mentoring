#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>  

using namespace std;

class Controller
{
public:
	void printList(vector<int> data);
};

//SortController
class SortController : public Controller
{
public:

	//Linear Sorts
	vector<int> bubbleSort(vector<int> data);
	vector<int> selectionSort(vector<int> data);
	vector<int> insertionSort(vector<int> data);

	//Binary Sorts
	vector<int> mergeSort(vector<int> data);
	vector<int> quickSort(vector<int> data);

private:
	//General swap function
	void swap(vector<int> &data, int a, int b);
	
	//Merge Sort Helper Functions
	void mergeSorter(vector<int> &data, int start, int end);
	void merge(vector<int> &data, int start, int end);

	//Quick Sort Helper Functions
	int medianThree(vector<int> &data, int start, int end);
	int partition(vector<int> &data, int start, int end, int median);
	void quickSorter(vector<int> &data, int start, int end);
};

class TestController : public Controller
{
private:
	struct TestObject
	{
		vector<int> data;
		string sortName;
	};

	vector<TestObject> testDataArray;
	vector<int> key, sourceData;

	//Helper functions
	void setSourceData(vector<int> data);
	string testChecker(vector<int> data);
	void createKey(vector<int> testData);

public:
	void addTest(string name, vector<int> data);
	void runTests(vector<int> testData, bool bDebug = false);
};