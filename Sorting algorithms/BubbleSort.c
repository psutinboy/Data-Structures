
#include <stdio.h>

#define n 8
int arr[8] = {80,70,60,50,40,30,20,10};
//int arr[8] = {30,10,30,80,90,60,70,80};

int swaps = 0;
int comps = 0;

void bubbleSort()
{
	int i, swapped, temp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		for (i = 0; i < n-1; i++)
		{
			comps++;
			if (arr[i] > arr[i+ 1])
			{
				swaps++;
				swapped = 1;
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
	}
}

int main()
{
	bubbleSort();

	for (int i = 0; i < n; i++)
	{
		printf("%d \n", arr[i]);
	}

	printf("Swap count: %d \n", swaps);
	printf("Comp count: %d \n", comps);

	return 0;
}