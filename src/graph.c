/* Sure, let's implement a simple undirected graph data structure in C. We'll use an adjacency list representation for the graph. Each vertex will have a list of adjacent vertices. */
/*  */
/* First, include the necessary headers for the code: */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
/* ``` */
/*  */
/* Define the structures for our graph: */
/*  */
/* ```c */
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;
/* ``` */
/*  */
/* Now, we can implement functions to create a graph, add an edge, remove an edge, print the graph, and free the graph. */
/*  */
/* ```c */
// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size of array is V
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void insertEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src.
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to remove an edge from the graph
void removeEdge(Graph* graph, int src, int dest) {
    AdjListNode** current = &graph->array[src].head;
    
    while (*current != NULL) {
        if ((*current)->dest == dest) {
            AdjListNode* temp = *current;
            *current = (*current)->next;
            free(temp);
            break;
        }
        current = &(*current)->next;
    }

    current = &graph->array[dest].head;

    while (*current != NULL) {
        if ((*current)->dest == src) {
            AdjListNode* temp = *current;
            *current = (*current)->next;
            free(temp);
            break;
        }
        current = &(*current)->next;
    }
}

// Function to print the graph
void showGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Function to free the graph
void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl) {
            AdjListNode* temp = pCrawl;
            pCrawl = pCrawl->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

// Main function to test the above functions
int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    insertEdge(graph, 0, 1);
    insertEdge(graph, 0, 4);
    insertEdge(graph, 1, 2);
    insertEdge(graph, 1, 3);
    insertEdge(graph, 1, 4);
    insertEdge(graph, 2, 3);
    insertEdge(graph, 3, 4);

    printf("Graph before removing an edge:\n");
    showGraph(graph);

    removeEdge(graph, 1, 4);

    printf("\nGraph after removing an edge:\n");
    showGraph(graph);

    freeGraph(graph);

    return 0;
}
/* ``` */
/*  */
/* This implementation covers the creation of a graph, addition and removal of edges, visual representation, and cleanup of memory. Each function ensures the proper handling and manipulation of the graph's adjacency list. */
