/* Sure, I'll provide a simple implementation of a Queue data structure in C. This will include the `enqueue`, `dequeue`, `peek`, `size`, and `isEmpty` functions. The implementation will use a linked list to facilitate dynamic resizing. */
/*  */
/* Here is the complete code: */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to get the size of the queue
int size(Queue* queue) {
    return queue->size;
}

// Function to add an element to the rear of the queue (enqueue)
void enqueue(Queue* queue, int data) {
    Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// Function to remove an element from the front of the queue (dequeue)
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

// Function to get the front element of the queue (peek)
int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->data;
}

// Function to delete the queue and free memory
void deleteQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

// Main function for testing the queue implementation
int main() {
    Queue* queue = createQueue();

    printf("Enqueueing 1, 2, 3...\n");
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    printf("Queue size: %d\n", size(queue));
    printf("Front element: %d\n", peek(queue));

    printf("Dequeuing...\n");
    printf("Dequeued element: %d\n", dequeue(queue));
    printf("Queue size: %d\n", size(queue));

    printf("Front element: %d\n", peek(queue));
    printf("Queue is empty: %d\n", isEmpty(queue));

    enqueue(queue, 4);
    printf("Enqueueing 4...\n");
    printf("Front element: %d\n", peek(queue));

    deleteQueue(queue);
    printf("Queue deleted.\n");

    return 0;
}
/* ``` */
/*  */
/* ### Explanation: */
/* 1. **Node Structure**: Represents an element in the queue containing the data and a pointer to the next node. */
/* 2. **Queue Structure**: Contains pointers to the front and rear nodes and a size counter. */
/* 3. **createNode**: Allocates memory for a new node and initializes it with data. */
/* 4. **createQueue**: Allocates memory for an empty queue and initializes it. */
/* 5. **isEmpty**: Checks if the queue is empty. */
/* 6. **size**: Returns the size of the queue. */
/* 7. **enqueue**: Adds a new element to the rear of the queue. */
/* 8. **dequeue**: Removes and returns the front element of the queue. */
/* 9. **peek**: Returns the front element without removing it. */
/* 10. **deleteQueue**: Completely frees the memory allocated for the queue. */
/* 11. **main**: Tests the implemented queue functions. */
