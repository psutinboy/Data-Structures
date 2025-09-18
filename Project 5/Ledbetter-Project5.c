// Area

#include <stdio.h>
#include <stdlib.h>

// Problem definition (Data set 0)
// see end of file for more problem definitions
// also see
// https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html
#define N 24
int capacity = 6404180;
int weightArr[N] =  {382745,
                     799601,
                     909247,
                     729069,
                     467902,
                     44328,
                     34610,
                     698150,
                     823460,
                     903959,
                     853665,
                     551830,
                     610856,
                     670702,
                     488960,
                     951111,
                     323046,
                     446298,
                     931161,
                     31385,
                     496951,
                     264724,
                     224916,
                     169684
                    };
int profitArr[N] =  { 825594,
                      1677009,
                      1676628,
                      1523970,
                      943972,
                      97426,
                      69666,
                      1296457,
                      1679693,
                      1902996,
                      1844992,
                      1049289,
                      1252836,
                      1319836,
                      953277,
                      2067538,
                      675367,
                      853655,
                      1826027,
                      65731,
                      901489,
                      577243,
                      466257,
                      369261
                    };
// end problem definition

int choiceArr[N]; // binary vector that represents the current choice we are
// examining

int bestChoice[N]; // holds the best solution we have found so far
int bestProfit;    // the best solution's corresponding profit
int bestWeight;    // "    " weight

int numCalls; // keep track of calls

int future[N + 1];

void calcFuture() {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			future[i] +=
			    profitArr[j]; // represents the max possible future profits if we
			// could take every element at position i and after
		}
	}
	future[N + 1] = 0;
}

int calcProfit() {
	int i, result = 0;

	for (i = 0; i < N; i++) {
		result += choiceArr[i] * profitArr[i];
	}

	return result;
}

void copyChoice() {
	int i;

	for (i = 0; i < N; i++) {
		bestChoice[i] = choiceArr[i];
	}
}

double DynamicUB(int position, int curWeight, int curProfit) {
	// int accWeight = curWeight;
	double accProfit = curProfit;
	int i = position;

	while (i < N && curWeight + weightArr[i] <= capacity) {
		curWeight += weightArr[i];
		accProfit += profitArr[i];
		i++;
	}

	// add a fraction of next item if we can
	if (i < N) {
		accProfit += (capacity - curWeight) * ((double) profitArr[i] / (double) weightArr[i]);
	}
	return accProfit;
}

void genProfits(int position, int curWeight, int curProfit) {
	int weight, profit;

	numCalls++;

	if (position == N) {
		profit = calcProfit();
		weight = curWeight;

		if (weight <= capacity) {
			if (profit > bestProfit) {
				bestProfit = profit;
				bestWeight = weight;
				copyChoice();
			}
		}
	} else {
		// Do take the item
		// but only if it wont overflow the sack
		// also take it if and only if getting a better profit than best profit is
		// possible
		if (curWeight + weightArr[position] <= capacity) {
			choiceArr[position] = 1;
			genProfits(position + 1, curWeight + weightArr[position],
			           curProfit + profitArr[position]);
		}

		// Do not take the item

		if (DynamicUB(position + 1, curWeight, curProfit) > bestProfit)
			// curProfit + future[position + 1] > bestProfit)
		{
			choiceArr[position] = 0;
			genProfits(position + 1, curWeight, curProfit);
		}
	}
}

void orderByPWRatio() {
	int i, j, k;
	double pw[N];
	int temp2;
	int max;
	double temp;

	for (i = 0; i < N; i++) {
		// pw[i] = (double)profitArr[i];
		pw[i] = (double)profitArr[i] / (double)weightArr[i];
	}

	// selection sort
	for (i = 0; i < N - 1; i++) {
		max = i;
		for (j = i + 1; j < N; j++) {
			if (pw[j] > pw[max]) {
				max = j;
			}
		} // at the end of this loop max has the largest pw ratio
		if (max != i) {
			// swap data in locations max, i
			temp = pw[i];
			pw[i] = pw[max];
			pw[max] = temp;

			temp2 = weightArr[i];
			weightArr[i] = weightArr[max];
			weightArr[max] = temp2;

			temp2 = profitArr[i];
			profitArr[i] = profitArr[max];
			profitArr[max] = temp2;
		}
	}
}

int main() {
	int i;
	orderByPWRatio();
	calcFuture();
	genProfits(0, 0, 0);

	printf("Optimal solution is (choice array):\n");
	for (i = 0; i < N; i++) {
		printf("weight %d, profit %d \n", weightArr[i], profitArr[i]);
		printf("%d \n", bestChoice[i]);
	}
	printf("****************\n");
	printf("Solution weight is %d:\n", bestWeight);
	printf("Solution profit is %d:\n", bestProfit);
	printf("****************\n");
	printf("Recursive calls: %d\n", numCalls);
	return 0;
}

/* sample data sets

//data set 0

#define N 4
int capacity = 9;
int weightArr[N] =  { 6,
  3,
 3,
  1};
int profitArr[N] =  {  3,
  8 ,
 2,
  3};

// data set 1


#define N 10
int capacity = 165;
int weightArr[N] =  {23,
                     31,
                     29,
                     44,
                     53,
                     38,
                     63,
                     85,
                     89,
                     82
                    };
int profitArr[N] =  {92,
                     57,
                     49,
                     68,
                     60,
                     43,
                     67,
                     84,
                     87,
                     72
                    };


// data set 2

#define N 15
int capacity = 750;
int weightArr[N] =  {70,
 73,
 77,
 80,
 82,
 87,
 90,
 94,
 98,
106,
110,
113,
115,
118,
120};
int profitArr[N] =  {135,
139,
149,
150,
156,
163,
173,
184,
192,
201,
210,
214,
221,
229,
240};

// data set 3



#define N 24
int capacity = 6404180;
int weightArr[N] =  {382745,
799601,
909247,
729069,
467902,
 44328,
 34610,
698150,
823460,
903959,
853665,
551830,
610856,
670702,
488960,
951111,
323046,
446298,
931161,
 31385,
496951,
264724,
224916,
169684};
int profitArr[N] =  { 825594,
1677009,
1676628,
1523970,
 943972,
  97426,
  69666,
1296457,
1679693,
1902996,
1844992,
1049289,
1252836,
1319836,
 953277,
2067538,
 675367,
 853655,
1826027,
  65731,
 901489,
 577243,
 466257,
 369261};











*/
