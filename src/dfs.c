/* Certainly! Here is an implementation of the Depth First Search (DFS) algorithm in C using a recursive function. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Graph structure
typedef struct {
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}

// Recursive DFS function
void DFSUtil(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// DFS traversal function
void DFS(Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }

    DFSUtil(graph, startVertex, visited);

    free(visited);
}

// Main function to test the DFS implementation
int main() {
    int vertices = 4; // Example: 4 vertices numbered 0 to 3
    Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);

    printf("Depth First Traversal starting from vertex 2:\n");
    DFS(graph, 2);

    // Cleanup
    free(graph);

    return 0;
}
/* ``` */
/*  */
/* ### Explanation: */
/*  */
/* 1. **Headers**: The necessary headers (`stdio.h` for input/output and `stdlib.h` for dynamic memory allocation) are included at the beginning. */
/*  */
/* 2. **Graph Structure**: The `Graph` structure is defined to store the number of vertices and the adjacency matrix. */
/*  */
/* 3. **Create Graph**: `createGraph()` initializes the graph with a given number of vertices and sets all edges to `0`. */
/*  */
/* 4. **Add Edge**: `addEdge()` adds an edge from `src` to `dest` in the graph. */
/*  */
/* 5. **DFS Utility Function**: `DFSUtil()` is a recursive function that visits vertices and prints them in DFS order. It marks each vertex as visited and recursively calls itself for each adjacent vertex. */
/*  */
/* 6. **DFS Traversal Function**: `DFS()` initializes the visited array and calls `DFSUtil()` to start the traversal from the given starting vertex. */
/*  */
/* 7. **Main Function**: The `main()` function tests the DFS implementation by creating a graph, adding edges, and starting the traversal from vertex 2. */
/*  */
/* ### Usage: */
/* Run the program. It will print the vertices of the graph in the depth-first order starting from vertex 2. You can modify the example graph and vertices as needed to test different scenarios. */
/*  */
