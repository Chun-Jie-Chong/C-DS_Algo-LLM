/* Sure, here is a complete implementation of a Singly Linked List in C that includes insert, delete, and viewList functions. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Function to insert a node at the beginning
void insert(struct Node **head, int data) {
    // Create a new node
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = data;

    // Make next of new node as head
    new_node->next = *head;

    // Move the head to point to the new node
    *head = new_node;
}

// Function to delete the first occurrence of a given key
void deleteNode(struct Node **head, int key) {
    // Store head node
    struct Node *temp = *head, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head = temp->next; // Changed head
        free(temp);         // Free old head
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}

// Function to print linked list
void viewList(struct Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Main function to test the linked list
int main() {
    // Start with the empty list
    struct Node *head = NULL;

    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);

    printf("Created Linked list: ");
    viewList(head);

    deleteNode(&head, 2);
    printf("Linked list after deletion of 2: ");
    viewList(head);

    return 0;
}
/* ``` */
/*  */
/* ### Explanation: */
/* 1. **Node Structure**: */
/*    - Each node contains integer data and a pointer to the next node. */
/*  */
/* 2. **Insert Function**: */
/*    - Inserts a new node at the beginning of the list. It updates the head pointer to the new node. */
/*  */
/* 3. **Delete Function**: */
/*    - Deletes the first occurrence of a given key. It takes care of updating the pointers and freeing memory. */
/*  */
/* 4. **ViewList Function**: */
/*    - Prints out all the elements of the linked list in order. It follows the `next` pointers from the head to the end of the list. */
/*  */
/* 5. **Main Function**: */
/*    - Demonstrates the use of insert, delete, and viewList functions. */
/*  */
/* This implementation is quite basic but covers the essential operations needed for managing a singly linked list in C. */
