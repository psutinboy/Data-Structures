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
    if (map[row][col] != '^') {
        return 0;
    }
    
    map[row][col] = '#'; //marks as visited
    
    int area = 1;
    area += AreaR(row - 1, col); // up
    area += AreaR(row + 1, col); // down
    area += AreaR(row, col - 1); // left
    area += AreaR(row, col + 1); // right
    
    return area;
}

// Add function AreaI - it should return the area of the body of water
// associated with row, col input. Calculate it iteratively. use queue
int AreaI(int row, int col)
{
    typedef struct {
        int row, col;
    } QueueNode;
    
    QueueNode queue[rowDim * colDim];
    int front = 0, rear = 0;
    int area = 0;
    
    if (map[row][col] != '^' && map[row][col] != '#') {
        return 0;
    }
    
    char targetChar = map[row][col];
    
    queue[rear].row = row;
    queue[rear].col = col;
    rear++;
    
    int visited[rowDim][colDim];
    for (int i = 0; i < rowDim; i++) {
        for (int j = 0; j < colDim; j++) {
            visited[i][j] = 0;
        }
    }
    
    visited[row][col] = 1;
    
    while (front < rear) {
        QueueNode current = queue[front];
        front++;
        area++;
        
        if (map[current.row][current.col] == '^') {
            map[current.row][current.col] = '#';
        }
        
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];
            
            if (newRow >= 0 && newRow < rowDim && 
                newCol >= 0 && newCol < colDim && 
                !visited[newRow][newCol] &&
                (map[newRow][newCol] == '^' || map[newRow][newCol] == '#')) {
                
                visited[newRow][newCol] = 1;
                queue[rear].row = newRow;
                queue[rear].col = newCol;
                rear++;
            }
        }
    }
    
    return area;
}


int main()
{
	int row, col;

	printf("Enter row (integer): ");
	scanf("%d", &row);

	printf("Enter column (integer): ");
	scanf("%d", &col);

	printf("Area of body of water at row %d, column %d is %d units. \n", row, col, AreaR(row, col));
	printf("Area of body of water at row %d, column %d is %d units. \n", row, col, AreaI(row, col));
	printMap();
	return 0;
}