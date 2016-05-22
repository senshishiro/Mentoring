
#include "stdafx.h"
#include "sort.h"


void SortData::swap(vector<int> &data, int a, int b)
{
	int temp;

	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}

vector<int> SortData::bubbleSort(vector<int> data)
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

vector<int> SortData::selectionSort(vector<int> data)
{
	int size = data.size()-1;

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
			//printList(data);
		}	
	}
		return data;
}

vector<int> SortData::insertionSort(vector<int> data)
{
	int size = data.size() - 1;

	//starts checking from the second element
	for (int i = 1; i < size; i++)
	{
		//int key = data[i];

		//cout << "keys: " << i << endl;
		for (int j = i; j > 0; j--)
		{
			if (data[j-1] > data[j])
			{
				//cout << "keys: " << j-1 << " " << j << endl;
				//cout << data[j-1] << " " << data[j] << endl;
				swap(data, j-1, j);
				//printList(data);
			}
		}
	}

	return data;
}

void SortData::printList(vector<int> data)
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