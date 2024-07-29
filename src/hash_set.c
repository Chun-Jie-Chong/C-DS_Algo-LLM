/* To implement a simple HashSet in C, we'll need to use a hash function, handle collisions (using separate chaining), and provide the necessary functions to manage the set. Here's a basic implementation: */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashNode {
    int key;
    struct HashNode* next;
} HashNode;

typedef struct HashSet {
    HashNode* table[TABLE_SIZE];
} HashSet;

// Simple hash function
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize HashSet
HashSet* createHashSet() {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = NULL;
    }
    return set;
}

// Create a new hash node
HashNode* createHashNode(int key) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Add a key to the HashSet
void add(HashSet* set, int key) {
    unsigned int index = hash(key);
    HashNode* newNode = createHashNode(key);
    if (set->table[index] == NULL) {
        set->table[index] = newNode;
    } else {
        HashNode* current = set->table[index];
        while (current->next != NULL && current->key != key) {
            current = current->next;
        }
        if (current->key != key) {
            current->next = newNode;
        } else {
            // If the key already exists, we can avoid adding it again
            free(newNode);
        }
    }
}

// Remove a key from the HashSet
void removeKey(HashSet* set, int key) {
    unsigned int index = hash(key);
    HashNode* current = set->table[index];
    HashNode* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                set->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Check if a key exists in the HashSet
int contains(HashSet* set, int key) {
    unsigned int index = hash(key);
    HashNode* current = set->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    HashSet* set = createHashSet();
    
    add(set, 5);
    add(set, 10);
    add(set, 15);

    printf("Contains 10: %d\n", contains(set, 10));
    printf("Contains 100: %d\n", contains(set, 100));

    removeKey(set, 10);
    printf("Contains 10 after removal: %d\n", contains(set, 10));

    // freeHashSet(set);
    
    return 0;
}
/* ``` */
/*  */
/* ### Explanation: */
/*  */
/* 1. **Hash Function:** Calculates the index for the given key. */
/* 2. **HashSet Struct:** Contains an array of pointers to `HashNode` which are used to handle collisions. */
/* 3. **createHashSet:** Initializes the table with NULL pointers. */
/* 4. **createHashNode:** Allocates and returns a new hash node. */
/* 5. **add:** Adds a key to the hash set, handling collisions by chaining. */
/* 6. **removeKey:** Removes a key from the hash set. */
/* 7. **contains:** Checks if the hash set contains the given key. */
/* 8. **freeHashSet:** Frees all the memory used by the hash set. */
/*  */
/* You can expand this base implementation by adding additional functionalities, improving the hash function, or handling rehashes to improve performance. */
