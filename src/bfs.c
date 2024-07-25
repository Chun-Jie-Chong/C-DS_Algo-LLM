#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.c"

// Define a queue node structure
typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

// Define a queue structure
typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Create a new empty queue
Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Check if the queue is empty
bool isEmpty(Queue *q) {
    return q->front == NULL;
}

// Enqueue an element
void enqueue(Queue *q, int value) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear != NULL) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (q->front == NULL) {
        q->front = newNode;
    }
}

// Dequeue an element
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    int value = q->front->data;
    QueueNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

// Free the queue
void freeQueue(Queue *q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

bool bfs(Graph g, int nV, Vertex src, Vertex dest) {
    if (src == dest) {
        return true;
    }

    bool *visited = calloc(nV, sizeof(bool));
    Queue *q = createQueue();

    visited[src] = true;
    enqueue(q, src);

    while (!isEmpty(q)) {
        Vertex v = dequeue(q);

        for (int w = 0; w < nV; w++) {
            if (g->edges[v][w] != 0 && !visited[w]) {
                if (w == dest) {
                    free(visited);
                    freeQueue(q);
                    return true;
                }
                visited[w] = true;
                enqueue(q, w);
            }
        }
    }

    free(visited);
    freeQueue(q);
    return false;
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

//     printf("\nBFS starting from vertex 0:\n");
//     bfs(g, 0);

//     freeGraph(g);

//     return 0;
// }
