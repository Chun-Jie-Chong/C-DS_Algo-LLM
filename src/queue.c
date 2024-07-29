#include <stdio.h>
#include <stdlib.h>

// Definition of the Node structure
struct node {
    int data;
    struct node *next;
};

// Definition of the Queue structure
struct queue {
    struct node *front;
    struct node *rear;
    int count;
};

// Function to create a new queue
struct queue* create() {
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    if (!q) {
        printf("Memory allocation error\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}

// Function to enqueue an element into the queue
void enqueue(struct queue *q, int x) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

// Function to dequeue an element from the queue
int dequeue(struct queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    struct node *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->count--;
    return data;
}

// Function to get the size of the queue
int size(struct queue *q) {
    return q->count;
}

// Main function for testing
int main() {
    struct queue *q = create();

    enqueue(q, 10); // Enqueue 10
    enqueue(q, 20); // Enqueue 20
    enqueue(q, 30); // Enqueue 30
    // viewQueue(q);   // Queue should be 10 -> 20 -> 30 -> NULL

    printf("Dequeued: %d\n", dequeue(q)); // Dequeue (should be 10)
    // viewQueue(q);   // Queue should be 20 -> 30 -> NULL

    printf("Queue size: %d\n", size(q));  // Size should be 2

    enqueue(q, 40); // Enqueue 40
    // viewQueue(q);   // Queue should be 20 -> 30 -> 40 -> NULL

    printf("Dequeued: %d\n", dequeue(q)); // Dequeue (should be 20)
    // viewQueue(q);   // Queue should be 30 -> 40 -> NULL

    printf("Queue size: %d\n", size(q));  // Size should be 2

    return 0;
}
