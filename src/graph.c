#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct GraphRep {
    int **edges;  // adjacency matrix
    int nV;       // #vertices
    int nE;       // #edges
} GraphRep;

typedef GraphRep *Graph;
typedef struct Edge {
    int v;
    int w;
} Edge;
typedef int Vertex;

// Create a new graph with V vertices
Graph newGraph(int V) {
    Graph g = malloc(sizeof(GraphRep));
    g->nV = V;
    g->nE = 0;
    g->edges = malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
    }
    return g;
}

// Insert an edge into the graph
void insertEdge(Graph g, Edge e) {
    int v = e.v, w = e.w;
    if (g->edges[v][w] == 0) {
        g->edges[v][w] = 1;
        g->edges[w][v] = 1;  // For undirected graph
        g->nE++;
    }
}

// Remove an edge from the graph
void removeEdge(Graph g, Edge e) {
    int v = e.v, w = e.w;
    if (g->edges[v][w] != 0) {
        g->edges[v][w] = 0;
        g->edges[w][v] = 0;  // For undirected graph
        g->nE--;
    }
}

// Check if there is an edge between vertex v and vertex w
bool adjacent(Graph g, Vertex v, Vertex w) {
    return g->edges[v][w] != 0;
}

// Display the graph
void showGraph(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        for (int j = 0; j < g->nV; j++) {
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}

// Free the graph
void freeGraph(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

// Main function for testing
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

//     removeEdge(g, e3);
//     printf("\nGraph adjacency matrix after removing edge (1, 2):\n");
//     showGraph(g);

//     freeGraph(g);

//     return 0;
// }
// AFL - graph.c
// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     FILE *file = fopen(argv[1], "r");
//     if (!file) {
//         perror("Could not open input file");
//         return EXIT_FAILURE;
//     }

//     int V;
//     if (fscanf(file, "%d", &V) == 1) { // Read number of vertices
//         Graph g = newGraph(V);

//         char command[10];
//         while (fscanf(file, "%s", command) != EOF) {
//             Edge e;
//             if (fscanf(file, "%d %d", &e.v, &e.w) == 2) { // Read edge vertices

//                 if (strcmp(command, "insert") == 0) {
//                     insertEdge(g, e);
//                 } else if (strcmp(command, "remove") == 0) {
//                     removeEdge(g, e);
//                 } else {
//                     fprintf(stderr, "Unknown command: %s\n", command);
//                 }
//             }
//         }
//         printf("Graph adjacency matrix:\n");
//         showGraph(g);
//         freeGraph(g);
//     }
//     fclose(file);

//     return EXIT_SUCCESS;
// }