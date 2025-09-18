
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define W 6
int weightArr[N+1] =  { 0,
                        3,
                        3,
                        2,
                        1,
                        2
                      };
int profitArr[N+1] =  { 0,
                        7,
                        3,
                        2,
                        1,
                        4
                      };
// end problem definition

int m[N + 1][W + 1];


int max(int a, int b)
{
	return (abs(a - b) + a + b) / 2;
}

int main()
{
	int i, j;

	for(i = 1; i <= N; i++)
	{
		for(j = 1; j <= W; j++)
		{
			if (weightArr[i] > j)
				m[i][j] = m[i - 1][j];
			else
			{
                m[i][j] = max(m[i-1][j] , m[i-1][j-weightArr[i]] + profitArr[i] );
			}
		}
	}


// print it
	for(i = 0; i <= N; i++)
	{
		for(j = 0; j <= W; j++)
		{
			printf("%d ", m[i][j]);
		}
		printf(" \n" );
	}

}
