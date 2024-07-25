#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.c"  // Include the graph implementation

// Recursive function for DFS
bool dfsRecursive(Graph g, Vertex v, Vertex dest, bool *visited) {
    if (v == dest) {
        return true;
    }

    visited[v] = true;

    for (int w = 0; w < g->nV; w++) {
        if (g->edges[v][w] && !visited[w]) {
            if (dfsRecursive(g, w, dest, visited)) {
                return true;
            }
        }
    }

    return false;
}

// Depth-First Search function
bool dfs(Graph g, int nV, Vertex src, Vertex dest) {
    bool *visited = calloc(nV, sizeof(bool));
    bool result = dfsRecursive(g, src, dest, visited);
    free(visited);
    return result;
}

// int main() {
//     int V = 5;
//     Graph g = newGraph(V);

//     Edge e1 = {0, 1};
//     Edge e2 = {0, 2};
//     Edge e3 = {1, 2};
//     Edge e4 = {1, 3};
//     Edge e5 = {2, 4};

//     insertEdge(g, e1);
//     insertEdge(g, e2);
//     insertEdge(g, e3);
//     insertEdge(g, e4);
//     insertEdge(g, e5);

//     printf("Graph adjacency matrix:\n");
//     showGraph(g);

//     Vertex src = 0;
//     Vertex dest = 4;
//     if (dfs(g, V, src, dest)) {
//         printf("\nThere is a path from %d to %d\n", src, dest);
//     } else {
//         printf("\nThere is no path from %d to %d\n", src, dest);
//     }

//     freeGraph(g);

//     return 0;
// }
