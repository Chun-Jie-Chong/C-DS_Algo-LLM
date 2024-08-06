/* Creating a HashMap from scratch in C involves several steps, including defining the structure for the HashMap, handling collisions with linked lists (separate chaining), and implementing essential functions such as insertion, deletion, and lookup. */
/*  */
/* Here's a step-by-step implementation of a simple HashMap in C: */
/*  */
/* 1. **Include necessary headers:** */
/* ```c */
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
/* ``` */
/*  */
/* 2. **Define data structures:** */
/* ```c */
   typedef struct HashNode {
       char *key;
       int value;
       struct HashNode *next;
   } HashNode;

   typedef struct {
       HashNode **buckets;
       int size;
   } HashMap;
/* ``` */
/*  */
/* 3. **Hash function:** */
/* ```c */
   unsigned long hashFunction(const char *key) {
       unsigned long hash = 0;
       while (*key) {
           hash = (hash << 5) + *key++;
       }
       return hash;
   }
/* ``` */
/*  */
/* 4. **Initialization function:** */
/* ```c */
   HashMap* createHashMap(int size) {
       HashMap *map = (HashMap*)malloc(sizeof(HashMap));
       map->size = size;
       map->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
       return map;
   }
/* ``` */
/*  */
/* 5. **Insertion function:** */
/* ```c */
   void insert(HashMap *map, const char *key, int value) {
       unsigned long hash = hashFunction(key) % map->size;
       HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
       newNode->key = strdup(key); // copy the key
       newNode->value = value;
       newNode->next = map->buckets[hash];
       map->buckets[hash] = newNode;
   }
/* ``` */
/*  */
/* 6. **Lookup function:** */
/* ```c */
   int get(HashMap *map, const char *key, int *value) {
       unsigned long hash = hashFunction(key) % map->size;
       HashNode *node = map->buckets[hash];
       while (node) {
           if (strcmp(node->key, key) == 0) {
               *value = node->value;
               return 1; // Key found
           }
           node = node->next;
       }
       return 0; // Key not found
   }
/* ``` */
/*  */
/* 7. **Deletion function:** */
/* ```c */
   void delete(HashMap *map, const char *key) {
       unsigned long hash = hashFunction(key) % map->size;
       HashNode *node = map->buckets[hash];
       HashNode *prev = NULL;
       while (node) {
           if (strcmp(node->key, key) == 0) {
               if (prev) {
                   prev->next = node->next;
               } else {
                   map->buckets[hash] = node->next;
               }
               free(node->key);
               free(node);
               return;
           }
           prev = node;
           node = node->next;
       }
   }
/* ``` */
/*  */
/* 8. **Cleanup function:** */
/* ```c */
   void freeHashMap(HashMap *map) {
       for (int i = 0; i < map->size; i++) {
           HashNode *node = map->buckets[i];
           while (node) {
               HashNode *temp = node;
               node = node->next;
               free(temp->key);
               free(temp);
           }
       }
       free(map->buckets);
       free(map);
   }
/* ``` */
/*  */
/* 9. **Main function for testing:** */
/* ```c */
//    int main() {
//        HashMap *map = createHashMap(10);

//        insert(map, "key1", 100);
//        insert(map, "key2", 200);
//        insert(map, "key3", 300);

//        int value;
//        if (get(map, "key1", &value)) {
//            printf("key1: %d\n", value);
//        } else {
//            printf("key1 not found\n");
//        }

//        if (get(map, "key4", &value)) {
//            printf("key4: %d\n", value);
//        } else {
//            printf("key4 not found\n");
//        }

//        delete(map, "key2");

//        if (get(map, "key2", &value)) {
//            printf("key2: %d\n", value);
//        } else {
//            printf("key2 not found\n");
//        }

//        freeHashMap(map);
//        return 0;
//    }
/* ``` */
/*  */
/* This implementation includes the basic features necessary for a functional HashMap, including initialization, insertion, lookup, deletion, and cleanup. It uses separate chaining to handle collisions and assumes keys are strings that need to be dynamically copied for storage within the map. */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    HashMap *map = createHashMap(10);
    char command[10];
    char key[100];
    int value;

    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "insert") == 0) {
            if (fscanf(file, "%s %d", key, &value) == 2) {
                insert(map, key, value);
            }
        } else if (strcmp(command, "lookup") == 0) {
            if (fscanf(file, "%s", key) == 1) {
                if (get(map, key, &value)) {
                    printf("%s: %d\n", key, value);
                } else {
                    printf("%s not found\n", key);
                }
            }
        } else if (strcmp(command, "delete") == 0) {
            if (fscanf(file, "%s", key) == 1) {
                delete(map, key);
            }
        } else {
            fprintf(stderr, "Unknown command: %s\n", command);
        }
    }

    fclose(file);
    freeHashMap(map);
    return 0;
}