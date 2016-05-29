#include "stdafx.h"
#include "sort.h"


int main()
{
	//Contains all sort algorithms
	SortController sortHelper;
	
	// Test Controller
	TestController test;
	
	//Test Data
	vector<int> sourceArr = { 5, 22, 2, 3, 0, 7,2,4, 1, 6, 12,9, 0, 3 };

	//Add Test Data to the tracker
	test.addTest("Insertion Sort", sortHelper.insertionSort(sourceArr));
	test.addTest("Selection Sort", sortHelper.selectionSort(sourceArr));
	test.addTest("Bubble Sort", sortHelper.bubbleSort(sourceArr));
	test.addTest("Merge Sort", sortHelper.mergeSort(sourceArr));
	test.addTest("Quick Sort", sortHelper.quickSort(sourceArr));
	
	//Run Tests
	test.runTests(sourceArr);
	//test.runTests(sourceArr, 1);

    return 0;
}

