// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143092;

// Hash table
node *table[N];

// Array containing all the words in the dictionary
char array[N][LENGTH + 1];

// Pointer to first element in linked list
node *head = NULL;

// Traversal pointer
node *cursor = NULL;

// Counter for words in the dictionary
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to obtain a hash value
    // int index = hash(word);

    // // Access linked list at that index in the hash table
    // cursor = table[index];

    // // Traverse linked list, looking for the word
    // while (cursor != NULL)
    // {
    //     // Checks if the word is in the dictionary
    //     if (strcasecmp(cursor->word, word) == 0)
    //     {
    //         return true;
    //     }
    //     // Moves cursor to the next node in the linked list
    //     cursor = cursor->next;
    // }


    // Maybe use pointer arithmetic to solve check
    for (int i = 0; i <= N; i++)
    {
        if(strcasecmp(array[i], word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// source: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);

    while (*word != 0)
    {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    // FILE *file = fopen(dictionary, "r");
    // if (!file)
    // {
    //     return false;
    // }

    int fd = open(dictionary, O_RDONLY);
    if (fd == -1)
    {
        return false;
    }

    // Character array
    char word[LENGTH + 1];

    // Get file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        perror("Couldn't get file size.\n");
        return false;
    }

    // mmap file
    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    // Go through file
    for (int i = 0; i < sb.st_size; i++)
    {
        /* strcpy(array[i], file_in_memory);
        word_count++; */
    }

    munmap(file_in_memory, sb.st_size);

    // Read strings from file one at a time
    // while (fscanf(file, "%s", word) != EOF)
    // {
    //     // Increment dictionary word count
    //     word_count++;

    //     // Create a new node for each word
    //     node *n = malloc(sizeof(node));
    //     if (n == NULL)
    //     {
    //         return false;
    //     }
    //     // Copy string from character array to node
    //     strcpy(n->word, word);

    //     // Hash word to obtain hash value
    //     int index = hash(word);

    //     // Set head pointer
    //     head = table[index];

    //     // If head is NULL, then the pointer will point to nothing.
    //     // Otherwise, the pointer will point to the previous head
    //     n->next = table[index];

    //     // Set the new node to be at the head of the current index
    //     table[index] = n;
    // }
    close(fd);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over hash table
    // for (int i = 0; i < N; i++)
    // {
    //     // Sets cursor to current iteration of hash table
    //     cursor = table[i];

    //     // Free nodes in linked list in current iteration of hash table
    //     while (cursor != NULL)
    //     {
    //         node *temp = cursor;
    //         cursor = cursor->next;
    //         free(temp);
    //     }

    // }
    return true;
}
