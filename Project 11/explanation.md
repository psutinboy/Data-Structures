# TSP Depth-First Search Optimization

## Overview
This document explains the pruning strategy implemented to reduce the number of recursive calls in the Travelling Salesman Problem (TSP) solver while maintaining correctness and finding the optimal solution.

## What Was Changed

### 1. Sorted Adjacency Lists by Edge Weight
Modified the `loadGraph()` function to sort each vertex's adjacency list in order of increasing edge weight. 

**Implementation Details:**
- Added a `VertexWeight` helper structure to pair vertices with their edge weights
- Added a `compareByWeight()` comparison function for `qsort()`
- After building the adjacency list for each vertex, the neighbors are sorted by their edge weights from smallest to largest

**Code Location:** Lines 36-89 in `Ledbetter-Project11.c`

### 2. Improved Pruning with Minimum Edge Bound
Implemented a smarter pruning condition in `depthFirst()` that uses the actual minimum edge weight from unvisited vertices:
```c
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
```

**Code Location:** Lines 100-119 in `Ledbetter-Project11.c`

## Why This Works

### The Key Insight: Exploration Order Matters
By sorting adjacency lists by increasing edge weight, the depth-first search explores **cheaper edges first**. This means:

1. **Better solutions are found earlier** in the search tree
2. **The `bestDistance` is updated to better values sooner**
3. **More branches can be pruned** because we have a tighter upper bound

### Example
Consider a vertex with edges of weight [5, 1, 3, 2]:
- **Without sorting:** DFS explores in arbitrary order [5, 1, 3, 2]
- **With sorting:** DFS explores in order [1, 2, 3, 5]

When we explore the cheaper edge (weight 1) first, we're more likely to complete a Hamiltonian cycle with a good total distance early on. Once we have this good solution, the pruning condition can eliminate expensive branches (like the one starting with weight 5) before they waste time exploring deep into the search tree.

### The Synergy Between Sorting and Pruning
The two optimizations work together powerfully:

1. **Sorting enables fast minimum edge lookup**: Because adjacency lists are sorted, finding the minimum edge from each unvisited vertex is O(1) - just look at the first element. Without sorting, this would require scanning all edges.

2. **Better bound calculation**: Instead of assuming each remaining vertex adds cost of 1 (like strategy 2), we calculate the actual minimum edge weight from unvisited vertices and use that in our lower bound estimate.

3. **Tighter pruning**: The bound `currentDistance + minEdge * remainingVertices` is much tighter than `currentDistance + 1 * remainingVertices`, allowing us to prune more branches while still being safe.

4. **Early good solutions**: Sorted edges ensure cheap paths are explored first, so `bestDistance` gets updated to good values early, making the pruning bound even more effective.

Neither optimization alone would be as effective:
- **Sorting without pruning:** Still explores all branches, just in a different order
- **Pruning without sorting:** Slower bound calculation and may explore expensive paths first

**Together:** Sorting enables efficient bound calculation AND ensures good solutions are found early, making pruning highly effective.

## Why Correctness Is Maintained

### Complete Search Guarantee
The algorithm still performs a **complete search** of the solution space:
- We visit every vertex exactly once (Hamiltonian cycle constraint)
- We only prune branches where `currentDistance >= bestDistance`, meaning they **cannot possibly** lead to a better solution
- Sorting changes the **order** of exploration, not **what** gets explored

### Pruning Safety
The pruning condition is **safe** because:
- We only prune after finding at least one complete cycle (`numCyclesFound > 0`)
- We calculate a **lower bound** on the remaining cost: `minEdge * remainingVertices`
- The actual cost to visit remaining vertices cannot be less than this (since minEdge is the smallest edge weight)
- If `currentDistance + lowerBound >= bestDistance`, then completing this path cannot improve on the best solution
- Therefore, pruned branches are guaranteed not to contain the optimal solution

### Why This Is Better Than Strategy 2
The previous strategy 2 used: `currentDistance + (N - numVisited) >= bestDistance`, which assumes each remaining vertex costs only 1. 

Our improved strategy uses: `currentDistance + minEdge * (N - numVisited) >= bestDistance`, where `minEdge` is the actual minimum edge weight from unvisited vertices.

Since edge weights in the graph are typically > 1, our lower bound is **tighter**, meaning we can prune more aggressively while still maintaining correctness.

## Expected Performance Improvement

### Theoretical Analysis
- **Worst case:** Still O(n!) for exploring all permutations, but with a much smaller constant factor
- **Average case:** Dramatic reduction in practice because:
  - Good solutions found in top portions of search tree
  - Expensive branches pruned early
  - Most of the factorial explosion is avoided

### Practical Impact
The combination of sorted adjacency lists and simple pruning should reduce the number of recursive calls by **orders of magnitude** compared to the unpruned version, while still guaranteeing the optimal solution is found.

The exact reduction depends on the graph structure, but for graphs with varied edge weights (like the one in this problem), the improvement is typically very significant.

## Conclusion
This optimization demonstrates that **algorithmic improvements don't always require complex techniques**. By simply changing the order in which we explore the search space, we enable a simple pruning condition to become highly effective, resulting in dramatic performance improvements while maintaining correctness.

