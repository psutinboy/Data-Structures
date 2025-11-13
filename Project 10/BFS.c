
#include <stdio.h>
#include <stdlib.h>

//QUEUE needed
typedef struct Node {
	struct Node *next;
	int  data;
} Node;


typedef struct LinkQueue {
	Node *front;
	Node *rear;
} LinkQueue;

LinkQueue *newQueue();
int isEmpty(LinkQueue *);
void destroyQueue(LinkQueue *);
void enqueue(LinkQueue *, int);
int dequeue(LinkQueue *);


// ***************************************************************************** END QUEUE
// Problem definition


/*
* 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
*/
#define N 20
int adjMat[N][N] = {
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 0
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  // 1
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},  // 2
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 3
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // 4
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},  // 5
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},  // 6
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 8
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 9
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // 10
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},  // 11
	{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 12
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 13
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 14
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},  // 15
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 16
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  // 17
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 18
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // 19
};

typedef struct Graph {
	int numVert;
	int *degree;
	int **adjList; // jagged array
	int *componentData; // componentData[5] = 2; means vertex 5 is in component 2 of graph
} Graph;





Graph *loadGraph()
{
	int i,j,k;

	Graph *newGraph = malloc(sizeof(Graph));

	// missing code
	return newGraph;
}

void destroyGraph(Graph *graph)
{
	// missing code
}

void printGraph(Graph *graph)
{
	for (int i = 0; i < graph->numVert; i++)
	{
		printf("Degree of vertex %d: %d",i,  graph->degree[i]);
		printf(", Adj List Data: ");
		for (int j = 0; j < graph->degree[i]; j++)
		{
			printf("%d, ", graph->adjList[i][j]);
		}
		printf("\n");
	}
	printf("***********\n");
	printf("Component data\n");
	for (int i = 0; i < graph->numVert; i++)
	{
		printf("Vertex %d belongs to component %d  \n", i, graph->componentData[i]);
	}
}

// bfs uses breadth first search to analyze graph connected components
// visits all vertices from start vertex and marks component data
// use component data to keep track of who is visited
void bfs(Graph *graph, int startVertex, int componentNum)
{
/*
queue = [start]
visited = {start}

while queue:
    node = queue.pop(0)
    process(node)  # Process here

    for neighbor in neighbors(node):
        if neighbor not in visited:
            visited.add(neighbor)  # Just mark
            queue.append(neighbor)
*/
}



int main()
{
	Graph *graph = loadGraph();

	int componentCount = 0;

	for (int i = 0; i < graph->numVert; i++)
	{
		if (graph->componentData[i] == -1)
		{
			componentCount++;
			bfs(graph, i, componentCount);
		}
	}

	printGraph(graph);
	destroyGraph(graph);
	return 0;
}
















LinkQueue *newQueue()
{
	LinkQueue *new = malloc(sizeof(LinkQueue));
	if (new != NULL)
	{
		new->front = NULL; // signifies empty queue;
		new->rear = NULL;
		return new;
	}
	else
	{
		printf("Memory allocation for queue failed!");
		return NULL;
	}
}

void destroyQueue(LinkQueue *this)
{
	while(!isEmpty(this))
	{
		dequeue(this);
	}
	free(this);
}

int isEmpty(LinkQueue *this)
{
	return (this->front == NULL);
}

void enqueue(LinkQueue *this, int x)
{

	Node *newNode = malloc(sizeof(Node));

	if (newNode == NULL)
	{
		printf("Memory allocation failed for a new node!");
		return;
	}

	newNode->data = x; // load data
	newNode->next = NULL; // VERY important... leave it off and see what happens bro

	if (isEmpty(this)) // also must set front if we enqueue first element
	{
		this->front = newNode;
		this->rear = newNode;
		return;
	}

	this->rear->next = newNode;
	this->rear = newNode;
}


int dequeue(LinkQueue *this)
{
	if(isEmpty(this))
	{
		printf("Empty queue, deqeue failed!\n");
		return -1;
	}

	Node *toRemove = this->front;
	this->front = this->front->next;

	if(isEmpty(this))
	{
		this->rear = NULL;
	}

	int x = toRemove->data;
	free(toRemove);

	return x;
}