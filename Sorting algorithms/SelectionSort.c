
#include <stdio.h>

#define n 8
int arr[8] = {80,70,60,50,40,30,20,10};
int swaps = 0;
int comps = 0;

void selectionSortR(int);

void selectionSort()
{
	int i, j, k, temp;

	for(i = 0; i < n - 1; i++)
	{
		k = i;                       // k keeps tracks of the index of the minimum value
		for(j = i + 1; j < n; j++)  // Scan forward from i + 1 and find the minimum value
		{
			comps++;
			if (arr[j] < arr[k])
				k = j;                     // If found an index with smaller array value, record it
		}
		if (k > i)                   // Swap the array values in position k and i
		{
			swaps++;
			temp = arr[k];
			arr[k] = arr[i];
			arr[i] = temp;
		}
	}
}

int main()
{
	selectionSort();
	//selectionSortR(n);
	for (int i = 0; i < n; i++)
	{
		printf("%d \n", arr[i]);
	}

	printf("Swap count: %d \n", swaps);
	printf("Comp count: %d \n", comps);

	return 0;
}

void selectionSortR(int pos)
{
	if (pos <= 1)
	    return;
	
	int i, maxIndex, temp;

	maxIndex = pos - 1;
	for(i = pos - 2;  i >= 0; i--)  // find max value scanning backward from pos - 1
	{
		comps++;
		if (arr[i] > arr[maxIndex])
		{
			maxIndex = i;
		}
	}
	if (maxIndex < pos - 1)
	{
		swaps++;
		temp = arr[maxIndex];
		arr[maxIndex] = arr[pos - 1];
		arr[pos - 1] = temp;
	}
	
	selectionSortR(pos - 1);
}


