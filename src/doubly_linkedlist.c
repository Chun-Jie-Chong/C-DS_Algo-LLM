/* Certainly! Below is a complete implementation of a Doubly Linked List in C, including necessary headers and functions for inserting, deleting, searching, and printing elements. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>

// Definition of a node in a doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Doubly Linked List structure
typedef struct DoublyLinkedList {
    Node* head;
} DoublyLinkedList;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insert(DoublyLinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to delete a node from the list
void delete(DoublyLinkedList* list, int data) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == data) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                list->head = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
    printf("Element %d not found.\n", data);
}

// Function to search for a node in the list
Node* search(DoublyLinkedList* list, int data) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to print the list
void print(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to free the entire list
void freeList(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
}

int main() {
    DoublyLinkedList list;
    list.head = NULL;

    // Test insertion
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    print(&list); // Output: 1 2 3

    // Test search
    Node* result = search(&list, 2);
    if (result != NULL) {
        printf("Found: %d\n", result->data); // Output: Found: 2
    } else {
        printf("Not found.\n");
    }

    // Test deletion
    delete(&list, 2);
    print(&list); // Output: 1 3

    delete(&list, 4); // Output: Element 4 not found.

    // Free the list
    freeList(&list);
    
    return 0;
}
/* ``` */
/*  */
/* Explanation of the code: */
/*  */
/* 1. **Node Definition**: The `Node` structure is defined with three members: `data`, `prev`, and `next` pointers. */
/* 2. **Doubly Linked List Structure**: Defined a `DoublyLinkedList` structure that contains a pointer to the head node. */
/* 3. **createNode**: Creates a new node with the provided data. */
/* 4. **insert**: Inserts a new node at the end of the list. */
/* 5. **delete**: Deletes a node with the specified data. */
/* 6. **search**: Searches for a node with the specified data. */
/* 7. **print**: Prints the data in the list. */
/* 8. **freeList**: Frees the entire list to avoid memory leaks. */
/* 9. **main**: Tests the implemented functions. */
/*  */
/* Ensure to compile the code using a C compiler like `gcc`. For example: */
/* ```sh */
/* gcc -o doubly_linked_list doubly_linked_list.c */
/* ./doubly_linked_list */
/* ``` */
