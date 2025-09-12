// Area

#include <stdio.h>

#define rowDim  20
#define colDim  30

char map[20][31] = {
        "...............^^^^^^^^^^^....",
        ".......^.....^^^^^^^^^^.......",
        "......^^^...^^^^^^^^^^........",
        "...^^^^^^^^^..................",
        ".^^^^^^^^^....................",
        "^^^^^^^^......................",
        "..............................",
        ".............^................",
        ".............^^...............",
        ".............^^^^.............",
        "............^^^^..............",
        "..............^...............",
        "^.............................",
        "..............................",
        "..........................^^^^",
        ".........................^^^^^",
        "........................^^^^^^",
        ".......................^^^^^^^",
        "........................^^^^^^",
        "..........................^^^^"
    };



void printMap()
{
	for (int i = 0; i < 20; i++)
	{
		printf("%s\n", map[i]);
	}
}

// Add function AreaR - it should return the area of the body of water
// associated with row, col input. Calculate it recursively.
int AreaR(int row, int col)
{
	return 0;
}

// Add function AreaI - it should return the area of the body of water
// associated with row, col input. Calculate it iteratively.
int AreaI(int row, int col)
{
	return 0;
}


int main()
{
	int row, col;

	printf("Enter row (integer): ");
	scanf("%d", &row);

	printf("Enter column (integer): ");
	scanf("%d", &col);

	getInput();
	printf("Area of body of water at row %d, column %d is %d units. \n", row, col, AreaR(row, col));
	printf("Area of body of water at row %d, column %d is %d units. \n", row, col, AreaI(row, col));
	printMap();
	return 0;
}