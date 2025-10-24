
#include <stdio.h>

#define N 12
int arr[12] = {10,23,51,94,16,37,62,85,40,73,29,75};

void swap(int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int leftNode(int i)
{
	// missing code
	return 0;
}

int rightNode(int i)
{
	// missing code
	return 0;
}

int parentNode(int i)
{
	// missing code
	return 0;
}

// return of 0 means node is good
// otherwise returns index of the child node to swap with
// length can be a number from 1 to N
int badNode(int i, int length) // use this with siftDown
{
	int left = leftNode(i);
	int right = rightNode(i);
	int max = 0;


	if (left > length - 1)     // node has no children
		return -1;
	else if (left == length - 1) // no has one left child
	{
		if (arr[i] < arr[left])
			return left;
		else
			return -1;
	}
	else // node has two children
	{
		if (arr[left] < arr[right])
			max = right;
		else
			max = left;
		if (arr[i] < arr[max])
			return max;
		else
			return -1;
	}
}

int badNodeUp(int i, int length) //use this with siftUp
{
	int parent = parentNode(i);

	if (arr[parent] < arr[i])
		return parent;
	else
		return -1;
}

void siftUp(int location, int length)
{
	int newLoc = -1;
	newLoc = badNodeUp(location, length);
	while (newLoc  != -1)
	{
		swap(location, newLoc);
		location = newLoc;
		newLoc = badNodeUp(newLoc, length);
	}
}

void siftDown(int location, int length)
{
	int newLoc = -1;
	newLoc = badNode(location, length);
	while (newLoc  != -1)
	{
		swap(location, newLoc);
		location = newLoc;
		newLoc = badNode(newLoc, length);
	}
}

void heapify()
{
	int i;

	for (i = N - 1; i >= 0; i--)
	{
		siftDown(i, N);
	}

	/*
		for (i = 1; i <= N - 1; i++)
		{
			siftUp(i, N);
		}
	*/

}

void heapSort()
{
	int i;
	heapify();

	for (i = N - 1; i >= 0; i--)
	{
		swap(0, i);
		siftDown(0, i);
	}
}


void printArr()
{
	int i;
	printf("*****\n");
	for (i = 0; i < N; i++)
		printf("%d \n", arr[i]);
	printf("*****\n");
}

int main()
{

	printArr();
	heapify();
	printArr();
	heapSort();
	printArr();
	return 0;
}



