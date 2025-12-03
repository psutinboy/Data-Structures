#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define MAX_NUM_STATES 100

typedef struct PuzzleState {
    int grid[3][3];
    int emptyRow;
    int emptyCol;
    char movedTile[10];
    char direction[10];
    int intEquiv;
} PuzzleState;



int maxRecursiveCalls = 2000000;

int numRecursiveCalls = 0;
int numPlanFound = 0;
int stepsInFirstPlan = 0;

PuzzleState plan[MAX_NUM_STATES];
int planSize = 0;

PuzzleState bestPlan[MAX_NUM_STATES];
int bestPlanSize = 0;

int solvedGrid[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };
PuzzleState solvedState;

/* Minimum moves: 31 */
int startGrid[3][3] = {
    {6, 4, 7},
    {8, 5, 0},
    {3, 2, 1}
};
int startEmptyRow = 1;
int startEmptyCol = 2;


// Function prototypes


void calcIntEquiv(PuzzleState *state);
int compareTo(PuzzleState *state1, PuzzleState *state2);
void initPuzzleState(PuzzleState *state, int grid[3][3], int emptyRow, int emptyCol, char *movedTile, char *direction);
int calculateManhattan(PuzzleState *state);

int planHas(PuzzleState *state);
void copyNewBestPlan(void);

void depthFirst(PuzzleState *currentState);
int tryMove(PuzzleState *src, PuzzleState *dest, int moveDir);
void printPlan(void);

// puzzle state functions

void calcIntEquiv(PuzzleState *state)
{
    int i, j;
    int result = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            result = 10 * result + state->grid[i][j];
        }
    }

    state->intEquiv = result;
}

int compareTo(PuzzleState *state1, PuzzleState *state2)
{
    if (state1->intEquiv == state2->intEquiv)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void initPuzzleState(PuzzleState *state, int grid[3][3], int emptyRow, int emptyCol, char *movedTile, char *direction)
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            state->grid[i][j] = grid[i][j];
        }
    }

    state->emptyRow = emptyRow;
    state->emptyCol = emptyCol;
    strcpy(state->movedTile, movedTile);
    strcpy(state->direction, direction);
    calcIntEquiv(state);
}

int calculateManhattan(PuzzleState *state)
{
    int i, j, value;
    int targetRow, targetCol;
    int distance = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            value = state->grid[i][j];
            if (value != 0)
            {
                targetRow = (value - 1) / 3;
                targetCol = (value - 1) % 3;
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }

    return distance;
}


// plan functions

int planHas(PuzzleState *state)
{
    int i;

    for (i = 0; i < planSize; i++)
    {
        if (compareTo(&plan[i], state) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void copyNewBestPlan(void)
{
    int i;

    bestPlanSize = planSize;

    for (i = 0; i < planSize; i++)
    {
        bestPlan[i] = plan[i];
    }
}


// 0 means empty moves up (tile moves down)
// 1 means empty down
// 2 means empty Left
// 3 means empty rigth
// return of 1 means move valid, 0 means invalid

int tryMove(PuzzleState *src, PuzzleState *dest, int moveDir)
{
    int newEmptyRow = src->emptyRow;
    int newEmptyCol = src->emptyCol;
    int tileRow, tileCol;
    char *dirName;
    switch (moveDir)
    {
        case 0:
            newEmptyRow = src->emptyRow - 1;
            dirName = "Down";
            break;
        case 1:
            newEmptyRow = src->emptyRow + 1;
            dirName = "Up";
            break;
        case 2:
            newEmptyCol = src->emptyCol - 1;
            dirName = "Right";
            break;
        case 3:
            newEmptyCol = src->emptyCol + 1;
            dirName = "Left";
            break;
        default:
            return 0;
    }


    if (newEmptyRow < 0 || newEmptyRow > 2 || newEmptyCol < 0 || newEmptyCol > 2)
        return 0;

    // copy
    *dest = *src;

    // tile to move is at new empty pos
    tileRow = newEmptyRow;
    tileCol = newEmptyCol;

     // record moved tile
    sprintf(dest->movedTile, "%d", src->grid[tileRow][tileCol]);
    strcpy(dest->direction, dirName);

    // swap
    dest->grid[src->emptyRow][src->emptyCol] = src->grid[tileRow][tileCol];
    dest->grid[tileRow][tileCol] = 0;
    dest->emptyRow = newEmptyRow;
    dest->emptyCol = newEmptyCol;

    calcIntEquiv(dest);

    return 1;
}



// dfs
void depthFirst(PuzzleState *currentState)
{
    int moveDir, i, j;
    int moveOrder[4];
    int moveManhattan[4];
    int numValid = 0;
    int temp, tempDir;
    PuzzleState tempState;

    if (numRecursiveCalls < maxRecursiveCalls)
    {
        numRecursiveCalls++;

        if (compareTo(currentState, &solvedState) == 0)
        {
            if ((planSize < bestPlanSize) || (numPlanFound == 0))
            {
                numPlanFound++;
                copyNewBestPlan();
                if (numPlanFound == 1)
                    stepsInFirstPlan = planSize - 1;
            }
        }
        else
        {
            // collect valid moves and their manhattan distances
            for (moveDir = 0; moveDir < 4; moveDir++)
            {
                if (tryMove(currentState, &tempState, moveDir))
                {
                    moveOrder[numValid] = moveDir;
                    moveManhattan[numValid] = calculateManhattan(&tempState);
                    numValid++;
                }
            }

            // sort moves by manhattan distance (ascending)
            for (i = 0; i < numValid - 1; i++)
            {
                for (j = 0; j < numValid - i - 1; j++)
                {
                    if (moveManhattan[j] > moveManhattan[j + 1])
                    {
                        temp = moveManhattan[j];
                        moveManhattan[j] = moveManhattan[j + 1];
                        moveManhattan[j + 1] = temp;

                        tempDir = moveOrder[j];
                        moveOrder[j] = moveOrder[j + 1];
                        moveOrder[j + 1] = tempDir;
                    }
                }
            }

            // try moves in order of best manhattan distance first
            for (i = 0; i < numValid; i++)
            {
                moveDir = moveOrder[i];

                // return if we are at max numb states
                if (planSize >= MAX_NUM_STATES)
                    continue;

                // insert move into plan array
                if (tryMove(currentState, &plan[planSize], moveDir))
                {
                    // see if it's worth exploring!
                    // prune if plansize + manhattan(&plan[planSize]) >= bestPlanSize
                    if (!planHas(&plan[planSize])
                        && ((numPlanFound == 0) || (planSize + 1 + calculateManhattan(&plan[planSize]) < bestPlanSize)))
                    {
                        planSize++;
                        depthFirst(&plan[planSize - 1]);
                        planSize--;
                    }
                }
            }
        }
    }
}

// print functionz

void printPlan(void)
{
    int i, j, k;
    PuzzleState *currentState;

    if (numPlanFound > 0)
    {
        if (numRecursiveCalls >= maxRecursiveCalls)
        {
            printf("Caution: Maximum recursive call limit reached\n");
            printf("Best plan may not be optimal!\n");
            printf("********************\n");
        }

        printf("Total plans found: %d\n", numPlanFound);
        printf("Recursive calls: %d\n", numRecursiveCalls);
        printf("Length of first plan found: %d\n", stepsInFirstPlan);
        printf("Length of best plan found: %d\n", bestPlanSize - 1);
        printf("\n");

        for (i = 0; i < bestPlanSize; i++)
        {
            currentState = &bestPlan[i];

            printf("********************\n");
            printf("%s - %s\n", currentState->movedTile, currentState->direction);
            printf("********************\n");

            for (j = 0; j < 3; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    printf("%d ", currentState->grid[j][k]);
                }
                printf("\n");
            }
        }
    }
    else
    {
        printf("No plans found\n");
    }
}



int main(void)
{
    int i, j;

    /* Initialize solved state */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            solvedState.grid[i][j] = solvedGrid[i][j];
        }
    }
    solvedState.emptyRow = 2;
    solvedState.emptyCol = 2;
    strcpy(solvedState.movedTile, "Solved");
    strcpy(solvedState.direction, "");
    calcIntEquiv(&solvedState);

    // create start
    initPuzzleState(&plan[0], startGrid, startEmptyRow, startEmptyCol, "Start", "");
    planSize = 1;

    // display initial puzzle
    printf("Initial Puzzle:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d ", startGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // solve
    printf("Solving...\n\n");
    depthFirst(&plan[0]);

    //print
    printPlan();

    return 0;
}
