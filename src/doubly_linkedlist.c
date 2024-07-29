#include <stdio.h>
#include <stdlib.h>

// Definition of the List structure
typedef struct list {
    double value;
    struct list *next, *prev;
} List;

// Function to create a new node with a given value
List* create(double value) {
    List *newNode = (List*)malloc(sizeof(List));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at a specific position
List* insert(List *list, double value, int pos) {
    List *newNode = create(value);

    if (pos == 0) {
        newNode->next = list;
        if (list != NULL) {
            list->prev = newNode;
        }
        return newNode;
    }

    List *current = list;
    for (int i = 0; i < pos - 1; i++) {
        if (current == NULL) {
            printf("Position out of range\n");
            free(newNode);
            return list;
        }
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;

    return list;
}

// Function to delete a node at a specific position
List* delete(List *list, int pos) {
    if (list == NULL) {
        printf("List is empty\n");
        return list;
    }

    List *current = list;

    if (pos == 0) {
        list = list->next;
        if (list != NULL) {
            list->prev = NULL;
        }
        free(current);
        return list;
    }

    for (int i = 0; i < pos; i++) {
        if (current == NULL) {
            printf("Position out of range\n");
            return list;
        }
        current = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);

    return list;
}

// Function to search for a value in the list
int search(List *list, double value) {
    int pos = 0;
    List *current = list;
    while (current != NULL) {
        if (current->value == value) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

// Function to print the list values
void print(List *list) {
    List *current = list;
    while (current != NULL) {
        printf("%.2f <-> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// Main function for testing
int main() {
    List *list = NULL;

    list = insert(list, 10.5, 0); // Insert 10.5 at position 0
    list = insert(list, 20.5, 1); // Insert 20.5 at position 1
    list = insert(list, 15.5, 1); // Insert 15.5 at position 1
    print(list);                  // List should be 10.5 <-> 15.5 <-> 20.5 <-> NULL

    list = delete(list, 1);       // Delete node at position 1
    print(list);                  // List should be 10.5 <-> 20.5 <-> NULL

    int pos = search(list, 20.5); // Search for 20.5
    printf("Position of 20.5: %d\n", pos); // Should print 1

    list = delete(list, 0);       // Delete node at position 0
    print(list);                  // List should be 20.5 <-> NULL

    list = delete(list, 0);       // Delete node at position 0
    print(list);                  // List should be NULL

    pos = search(list, 20.5);     // Search for 20.5
    printf("Position of 20.5: %d\n", pos); // Should print -1

    return 0;
}
