/* Certainly! Below is a C implementation of the Breadth-First Search (BFS) algorithm using a queue. We'll define the necessary headers, the queue data structure, and the BFS function itself. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Queue structure
typedef struct Queue {
    int *items;
    int front;
    int rear;
    int max_size;
} Queue;

// Function to create a queue
Queue* createQueue(int max_size) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(sizeof(int) * max_size);
    q->front = -1;
    q->rear = -1;
    q->max_size = max_size;
    return q;
}

// Function to check if the queue is empty
bool isEmpty(Queue *q) {
    return q->front == -1;
}

// Function to enqueue an element
void enqueue(Queue *q, int value) {
    if (q->rear == q->max_size - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

// Function to dequeue an element
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        exit(1);
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1; // Reset queue
    }
    return item;
}

// BFS function
void BFS(int graph[][5], int startVertex, int numVertices) {
    bool visited[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    Queue *q = createQueue(numVertices);

    visited[startVertex] = true;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);

        // Checking neighbors
        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
}

int main() {
    // Example graph as adjacency matrix (5 vertices)
    int graph[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };

    // Starting the BFS from vertex 0
    BFS(graph, 0, 5);

    return 0;
}
/* ``` */
/*  */
/* This code defines a `Queue` structure and implements the necessary queue operations: `enqueue`, `dequeue`, and `isEmpty`. The `BFS` function uses this queue to explore the graph starting from the provided start vertex. */
/*  */
/* The graph is represented as an adjacency matrix for simplicity. You can modify the size and content of the `graph` matrix and `numVertices` variable to work with different graphs. */
