// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 143093;

// Hash table
node *table[N];

// Keep track of loaded words
unsigned int total_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // Hash word to obtain a hash value
    unsigned int index = hash(word);
    node *ptr;
    ptr = table[index];
    // Traverse linked list at this index
    while (ptr != NULL) {
        // Compare words case insensitively
        if (strcasecmp(ptr->word, word) == 0) {
            return true;
        } 
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        // Guarantee case insensitivity
        char c = tolower(word[i]);
        // Multiply accumulator by a prime constant and add character
        hash_value = (hash_value * 31) + c;
    }
    // Return the remainder of the division to ensure the index is valid (0 to N-1)
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        return false;
    }
    // Read words from file one at a time
    char buffer[LENGTH+1];
    // Read each word until end of file
    while (fscanf(file, "%s", buffer) != EOF) {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }
        // Copy word into node
        strncpy(n->word, buffer, sizeof(buffer));
        // Insert node into hash table at appropriate index
        unsigned int index = hash(buffer);
        n->next = table[index];
        table[index] = n;
        // Increment word count
        total_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
 return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL) {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

