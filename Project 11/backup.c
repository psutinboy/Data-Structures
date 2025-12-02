
#include <stdio.h>
#include <stdlib.h>

// https://www.online-cpp.com/online_c_compiler
// Problem definition
#define N 20
int adjMat[N][N] = {
{0,1,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,2,0,0},
{1,0,2,2,2,0,0,2,0,2,1,0,0,0,0,0,0,2,0,0},
{0,2,0,1,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2},
{0,2,1,0,2,0,1,2,0,0,2,0,0,1,0,0,0,0,1,1},
{0,2,0,2,0,0,0,0,1,1,0,0,0,0,1,0,0,0,2,0},
{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,2,0,0,0},
{0,0,0,1,0,0,0,0,0,0,1,2,0,0,0,0,2,1,2,0},
{0,2,2,2,0,0,0,0,0,2,2,2,0,0,0,1,0,2,0,1},
{0,0,0,0,1,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
{0,2,0,0,1,0,0,2,2,0,0,0,0,0,0,0,1,0,2,1},
{1,1,2,2,0,1,1,2,0,0,0,1,0,2,0,2,0,0,1,2},
{0,0,0,0,0,0,2,2,0,0,1,0,0,0,0,0,0,1,1,0},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,2,0,1},
{0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,2,2,2,0},
{0,0,0,0,0,2,2,0,0,1,0,0,0,0,0,2,0,2,0,0},
{2,2,0,0,0,0,1,2,0,0,0,1,0,0,2,2,2,0,0,0},
{0,0,0,1,2,0,2,0,0,2,1,1,0,0,0,2,0,0,0,0},
{0,0,2,1,0,0,0,1,0,1,2,0,0,0,1,0,0,0,0,0}
};

typedef struct Graph {
  int numVert;
  int *degree;
  int **adjList; // jagged array
} Graph;

Graph *loadGraph() {
  int i, j, k;

  Graph *newGraph = malloc(sizeof(Graph));

  newGraph->numVert = N;
  newGraph->degree = malloc(N * sizeof(int));
  newGraph->adjList = malloc(N * sizeof(int *));
  // determine degrees and initialize adjList and component data
  for (i = 0; i < N; i++) {
    int deg = 0;
    for (j = 0; j < N; j++) {
      if (adjMat[i][j] != 0)
        deg++;
    }
    newGraph->degree[i] = deg;
    newGraph->adjList[i] = malloc(deg * sizeof(int));
    // second pass, determine actual adj list

    int count = 0;
    for (j = 0; j < N; j++) {
      if (adjMat[i][j] != 0) {
        newGraph->adjList[i][count] = j;
        count++;
      }
    }

    // Sort adjacency list by edge weight (simple bubble sort)
    for (j = 0; j < deg - 1; j++) {
      for (k = 0; k < deg - j - 1; k++) {
        int v1 = newGraph->adjList[i][k];
        int v2 = newGraph->adjList[i][k + 1];
        if (adjMat[i][v1] > adjMat[i][v2]) {
          // Swap
          newGraph->adjList[i][k] = v2;
          newGraph->adjList[i][k + 1] = v1;
        }
      }
    }
  }
  return newGraph;
}

void destroyGraph(Graph *graph) {
  for (int i = 1; i < graph->numVert; i++) {
    free(graph->adjList[i]);
  }
  free(graph->adjList);
  free(graph->degree);
  free(graph);
}

// global variables for simplicity
int numRecursiveCalls = 0; // records the number of recursive calls;
int numCyclesFound = 0;    // records the total Hamiltonian cycles found
int bestDistance = 0;      // records best solution found (distance travelled);
int currentPath[N];        // stores current path under consideration
int bestPath[N];           // stores best path found
int visited[N];            // keep track of we have visited
int startVertex = 0;       // start the search at vertex 0;

// note numVisited keeps track of how many vertices we have visited (basically
// the depth of the recursion)
void depthFirst(Graph *graph, int vertex, int numVisited, int currentDistance) {
  numRecursiveCalls++;
  
  // added pruning strategy 1 (not good enough)
  /*
  if (currentDistance >= bestDistance && numCyclesFound > 0)
  {
    return;
  }
  */

  // added pruning strategy 2 (do better than this)
  /*
  if (currentDistance + (N - numVisited) >= bestDistance && numCyclesFound > 0)
  {
    return;
  }
  */

   // Pruning with minimum edge bound
   // Since adjacency lists are sorted, first edge from each unvisited vertex is minimum
   if (numCyclesFound > 0) {
     int minEdge = 999999;
     for (int i = 0; i < graph->numVert; i++) {
       if (!visited[i] && graph->degree[i] > 0) {
         // First neighbor has minimum weight due to sorting
         int neighbor = graph->adjList[i][0];
         int edgeWeight = adjMat[i][neighbor];
         if (edgeWeight < minEdge) {
           minEdge = edgeWeight;
         }
       }
     }
     // Lower bound: current distance + minimum edge * remaining vertices
     if (currentDistance + minEdge * (graph->numVert - numVisited) >= bestDistance) {
       return;
     }
   }

  visited[vertex] = 1;
  currentPath[numVisited] = vertex;
  numVisited++;

  // if we numVisited == graph->numVert, we have visited all vertices
  // also need to check if we are adjacent to the original start vertex (cycle
  // condition)
  if ((numVisited == graph->numVert) && (adjMat[vertex][startVertex] > 0)) {
    // well we found a cycles
    int finalDistance = currentDistance + adjMat[vertex][startVertex];
    numCyclesFound++;
    if ((finalDistance < bestDistance) ||
        numCyclesFound ==
            1) // record if its shorter length OR the first cycle found
    {
      bestDistance = finalDistance;
      for (int i = 1; i < N; i++)
        bestPath[i] = currentPath[i];
    }
  } else {
    // have not found a cycle, process adjacent vertices
    int vertexDeg = graph->degree[vertex]; // gets the degree of current vertex
                                           // we are processing
    for (int i = 0; i < vertexDeg; i++) {
      int adjVert = graph->adjList[vertex][i]; // i-th vertex adjacent to vertex
      if (!visited[adjVert]) {
        depthFirst(graph, adjVert, numVisited,
                   currentDistance + adjMat[adjVert][vertex]);
      }
    }
  }

  // when you back track be sure to unvist
  visited[vertex] = 0;
}

void printResults();

int main() {
  Graph *graph = loadGraph();

  // visit startVertex
  //	visited[startVertex] = 1;
  //	currentPath[0] = startVertex;
  depthFirst(graph, startVertex, 0, 0);
  printResults();

  // free mem
  destroyGraph(graph);

  return 0;
}

void printResults() {
  printf("Total Hamiltonian cycles found %d \n", numCyclesFound);
  printf("Total recursive calls %d \n", numRecursiveCalls);
  printf("Shortest cycle is of distance %d \n", bestDistance);
  printf("**********\n");
  for (int i = 0; i < N; i++) {
    printf("Visit vertex %d \n", bestPath[i]);
  }
  printf("Return to vertex %d \n", startVertex);
  printf("**********\n");
}
