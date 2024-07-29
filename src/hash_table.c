/* Certainly! Below is a basic implementation of a HashTable in C. This implementation includes functions for initializing the table, inserting elements, searching for elements, and freeing up resources. */
/*  */
/* ```c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Definition of the HashTable's node
typedef struct HashNode {
    char *key;
    char *value;
    struct HashNode *next;
} HashNode;

// Definition of the HashTable
typedef struct {
    HashNode **table;
} HashTable;

// Create a new hash node
HashNode *create_node(char *key, char *value) {
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    return new_node;
}

// Free a hash node
void free_node(HashNode *node) {
    free(node->key);
    free(node->value);
    free(node);
}

// Hash function
unsigned int hash(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

// Initialize HashTable
HashTable *create_table() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (HashNode **)malloc(TABLE_SIZE * sizeof(HashNode *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Insert a key-value pair into the HashTable
void insert(HashTable *hashTable, char *key, char *value) {
    unsigned int index = hash(key);
    HashNode *new_node = create_node(key, value);

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = new_node;
    } else {
        HashNode *temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Search for a value by key in the HashTable
char *search(HashTable *hashTable, char *key) {
    unsigned int index = hash(key);
    HashNode *temp = hashTable->table[index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

// Delete a key-value pair from the HashTable
void delete(HashTable *hashTable, char *key) {
    unsigned int index = hash(key);
    HashNode *temp = hashTable->table[index];
    HashNode *prev = NULL;

    while (temp != NULL && strcmp(temp->key, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        // Key not found
        return;
    }

    if (prev == NULL) {
        hashTable->table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free_node(temp);
}

// Free up the HashTable
void free_table(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *temp = hashTable->table[i];
        while (temp != NULL) {
            HashNode *to_free = temp;
            temp = temp->next;
            free_node(to_free);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int main() {
    HashTable *hashTable = create_table();

    insert(hashTable, "name", "John Doe");
    insert(hashTable, "occupation", "Software Developer");
    insert(hashTable, "language", "C");

    printf("Name: %s\n", search(hashTable, "name"));
    printf("Occupation: %s\n", search(hashTable, "occupation"));
    printf("Language: %s\n", search(hashTable, "language"));

    delete(hashTable, "name");
    printf("Name after deletion: %s\n", search(hashTable, "name"));  // Should be NULL

    free_table(hashTable);

    return 0;
}
/* ``` */
/*  */
/* This code provides a simple HashTable implementation with basic functionalities such as insertion, searching, and deletion. We also perform resource cleanup to prevent memory leaks. */
