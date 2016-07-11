
#include "stdafx.h"
#include "sort.h"


//===================================================================
// Print List
void Controller::printList(vector<int> data)
{
	int size = data.size();

	for (int i = 0; i < size; i++)
	{
		cout << data[i];

		if (i == size - 1)
		{
			cout << endl;
		}
		else
		{
			cout << ", ";
		}
	}
}

//===================================================================
// Set test data
void TestController::setSourceData(vector<int> data)
{
	sourceData = data;
}

//===================================================================
// Sort Test Helper

string TestController::testChecker(vector<int> data)
{
	if (data == key)
	{
		return "PASSED";
	}
	else
	{
		return "FAILED";
	}
}

//===================================================================
// Add Test
// Creates a TestObject and adds it to the vector
void TestController::addTest(string name, vector<int> data)
{
	TestObject temp;

	temp.sortName = name;
	temp.data = data;

	//Add test object to array
	testDataArray.push_back(temp);
}

//===================================================================
// Create Key
// Uses STL sort to create key.

void TestController::createKey(vector<int> testData)
{
	key = testData;
	sort(key.begin(), key.end());
}

//===================================================================
// Run Checker
// Loops through all tests and runs it against the key
void TestController::runTests(vector<int> testData, bool bDebug)
{
	setSourceData(testData);
	createKey(testData);
	int size = testDataArray.size();

	cout << "-----------------------------------------------------------\n";
	
	cout << "Source : ";
	printList(testData);

	cout << "Key : ";
	printList(key);

	cout << "-----------------------------------------------------------\n";

	if ( size > 0 )
	{
		for (int i = 0; i < size; i++)
		{
			string results = testChecker(testDataArray[i].data);

			cout << testDataArray[i].sortName << " : " << results << endl;

			if (bDebug)
			{
				cout << testDataArray[i].sortName << " : ";
				printList(testDataArray[i].data);
			}
		}
	}
	else
	{
		cerr << "There is no test data";
	}
}

//===================================================================
// Swap
void SortController::swap(vector<int> &data, int a, int b)
{
	int temp;

	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}

//===================================================================
// Bubble Sort
// Compares current and next value, and swaps to asceding order. 
// Repeats until the array is sorted
//===================================================================
vector<int> SortController::bubbleSort(vector<int> data)
{
	bool sorted = true;
	int size = data.size();
	int count = 0;

	do
	{		
		sorted = true;
		count++;

		for (int i = 0; i < size - count; i++)
		{
			if (data[i] > data[i + 1])
			{
				swap(data, i, i + 1);
				sorted = false;
			}
		}
	} while (!sorted);	

	return data;
}

//===================================================================
// Selection Sort
// Finds the smallest value and swaps it with the current value
//===================================================================
vector<int> SortController::selectionSort(vector<int> data)
{
	int size = data.size();

	for (int i = 0; i < size; i++)
	{
		int minPos = i;
		
		for (int j = i + 1; j < size; j++)
		{
			if (data[minPos] > data[j])
			{
				minPos = j;
				//cout << "new min: "<< data[minPos] << endl;
			}
		}
		//if the numbers are the same don't swap	
		if (data[minPos] != data[i])
		{
			swap(data, i, minPos);
		}	
	}
		return data;
}

//===================================================================
// Insertion Sort
// Sorts Data by finding an elment smaller than the previous, then shifting it over
//===================================================================
vector<int> SortController::insertionSort(vector<int> data)
{
	int size = data.size();

	//starts checking from the second element. 
	// Zero element is checked below in data[j-1]
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			//Check if previous element is larger than current element
			if (data[j-1] > data[j])
			{
				//Swaps with previous element 
				swap(data, j-1, j);
			}
		}
	}
	return data;
}

//===================================================================
// Merge Sort
//===================================================================

//-------------------------------------------------------------------
// Merge Sort
// Wrapper function
vector<int> SortController::mergeSort(vector<int> data)
{
	int start = 0;
	int end = data.size();

	mergeSorter(data, start, end);
	return data;
}

//-------------------------------------------------------------------
// Merge Sorter
// Keeps splitting the data into single elements. Sorts and remerges everything as it goes back up.
void SortController::mergeSorter(vector<int> &data, int start, int end)
{
	//calculate mid point
	int mid = (end + start) / 2;

	//Base Case: return when there is one element
	if (end - start <= 1)
	{
		return;
	}
	//split and sort the halves	
	mergeSorter(data, start, mid);
	mergeSorter(data, mid, end);

	//merge
	merge(data, start, end);
}

//-------------------------------------------------------------------
//Merge function
// Compares the two section in the array, and stores it in a helper array.
// Helper array is copied back into the main array after sorting.
void SortController::merge(vector<int> &data, int start, int end)
{
	//calculate new mid point
	int mid = (end + start) / 2;
	int left = start;
	int right = mid;
	int counter = start;
	vector<int> temp = data;

	//Check if the left side or right side has reached the midpoint/end
	while (left < mid && right < end)
	{
		//comparison between the values from the two arrays
		if (data[left] <= data[right])
		{
			temp[counter] = data[left];
			left++;
		}
		else
		{
			temp[counter] = data[right];
			right++;
		}
		counter++;
	}

	//Add any remaining numbers from the left side
	while (left < mid)
	{
		temp[counter] = data[left];
		left++;
		counter++;
	}

	//Add any remaining numbers from the right side
	while (right < end)
	{
		temp[counter] = data[right];
		right++;
		counter++;
	}

	//Copy sorted values back to the original array
	data = temp;
}

//===================================================================
// Quick Sort
//===================================================================


//-------------------------------------------------------------------
// quickSort
// wrapper function
vector<int> SortController::quickSort(vector<int> data)
{
	int start = 0;
	int end = data.size() - 1;

	quickSorter(data, start, end);

	return data;
}

//-------------------------------------------------------------------
// quickSorter
// Sorts the array by moving all values less than the pivot to the left,
// and all values larger to the right.
void SortController::quickSorter(vector<int> &data, int start, int end)
{
	if (start<end)
	{
		//Find Median
		int median = medianThree(data, start, end);

		//partition and find location of new pivots
		int pivot = partition(data, start, end, median);

		//quicksort first half before pivot
		quickSorter(data, start, pivot-1);

		//quicksort second half after pivot
		quickSorter(data, pivot + 1, end);		
	}
	//BASE CASE: when end is greater than start, return.
	else
	{
		//cout << "Base >> start: " << start << " end: " << end << endl;
		return;
	}

}

//-------------------------------------------------------------------
// medianThree
// Finds the mid element, and does a light sort between start and end
// Reduces chance of worst case
int SortController::medianThree(vector<int> &data, int start, int end)
{
	int mid = (start + end) / 2;

	//sort start, end, and mid in the array.
	if (data[start] > data[mid])
	{
		swap(data, start, mid);
	}

	if (data[start]>data[end])
	{
		swap(data, start, end);
	}

	if (data[mid] > data[end])
	{
		swap(data, mid, end);
	}

	return mid;
}

//-------------------------------------------------------------------
// partition
// Pivot is moved to the start of the array. Lower and Higher values to the right are swapped.
// Pivot is restored to the last lower position.
int SortController::partition(vector<int> &data, int start, int end, int median)
{
	//Start is increased by one to avoid the pivot at the beginning.
	int i = start+1;
	int j = end;
	int pivot = data[median];

	//Move the pivot to the front of the array
	swap(data, start, median);

	while (true)
	{
		//Find an element lower than the pivot
		while (data[i] < pivot)
		{
			i++;
		}

		//Find an element larger than the pivot while traversing the array backwards
		while (data[j] > pivot)
		{
			j--;
		}

		//Stop the loop when i crosses j
		if (i >= j)
		{
			break;
		}
		else
		{
			//Swap the lower and larger element in the array
			swap(data, i, j);
		}
	}

	//restore pivot back to center. Just before i and j crossed.
	swap(data, start, i-1);

	//Send back new end index
	return i-1;
}
