#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createnode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at a specified position
void insert(struct Node** head, int pos, int val) {
    struct Node* newNode = createnode(val);
    
    if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    
    struct Node* current = *head;
    for (int i = 0; current != NULL && i < pos - 1; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Position out of range\n");
        free(newNode);
        return;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

// Function to delete a node at a specified position
void deletion(struct Node** head, int pos) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node* temp = *head;
    
    if (pos == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    
    struct Node* prev = NULL;
    for (int i = 0; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    
    prev->next = temp->next;
    free(temp);
}

// Function to print the values in the list
void viewList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    
    insert(&head, 0, 1);
    insert(&head, 1, 2);
    insert(&head, 2, 3);
    insert(&head, 1, 4);
    
    printf("List after insertions: ");
    viewList(head);
    
    deletion(&head, 2);
    printf("List after deletion at position 2: ");
    viewList(head);
    
    deletion(&head, 0);
    printf("List after deletion at position 0: ");
    viewList(head);
    
    return 0;
}
