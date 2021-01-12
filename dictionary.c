// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dictionary.h"
#include <cs50.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Declaring the word counter outside of load() so that size() can return it
int numberOfWords = 0;

// Character array for load function to read words into
char buffer[LENGTH + 1];

// Number of buckets in hash table (randomly chose the number of letters in alphabet)
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // Hashing the word
    int index = hash(word);
    
    // For loop iterating through linked list
    // Using a trav node being equal to head (table itself)
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp -> next)
    {
        // stcasecmp here makes spell-checking case-sensitive
        if (strcasecmp(word, tmp -> word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number, source: https://stackoverflow.com/questions/60883447/have-a-problem-when-trying-to-check-for-my-solution-on-pset5-cs50
// The guy doesn't have any source in his code which leads me to think it's is own. The rest of his code however..
unsigned int hash(const char *word)
{
    // To study better, have to understand how hashing works exactly
    // First it checks if the first char of word is a letter
   if ((isalpha(word[0]) > 0))
   {
       // If it is, it converst it to lower case and it subtracts 'a'
       // Using ASCII here: if the letter is a then it will return 0 (97-97), if z 25 (122-95) and everything in between will be 1...24
       return tolower(word[0]) - 'a';
   }
   else
   {
       // if the first character of word is not a letter then it's indexed in the linked list associated with array 26 of hash table
       return 26;
   }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening the dictionary file with fopen()
    FILE *file = fopen(dictionary,"r");
    
    // Checking that it doesn't return NULL
    if (file == NULL)
    {
        return false;
    }
    

    // While loop to read through all the words in the newly opened file
    // Using the return value of fscanf as condition
    while (fscanf(file, "%s", buffer) != EOF)
    {
        
        // Allocating memory
        node *n = malloc(sizeof(node));
    
        // Checking for NULL
        if (n == NULL)
        {
         return false;
        }
        
        // Copying word from buffer to node. here key concept is that you're copying word stored in node (n -> word), not any word
        strcpy(n -> word, buffer);
        
        // Setting next pointer of node to null. I think this is necessary but not sure 100%
        n -> next = NULL;
        
        // Hashing the word. Hash fucntion returns an int that we will call index here
        int index = hash(n -> word);

        // Inserting node into hash table
        // The table[index] is ultimately the head of the list I want to add the word to
        // If the head is pointing to nothing I can have the head point to this node
        if (table[index] == NULL)
        {
            // Head of list pointing to node
            table[index] = n;
            // Keeping count
            numberOfWords++;
        }

        // If the head is already pointing at something I need to have the node point at that something, then the head point to this node
        else
        {
            // Node pointing to what head is pointing at (first node of list). Remember that arrays are pointers! 
            n -> next = table[index];
            // Table (head) pointing at node (now first node of list)
            table[index] = n;
            // Keeping count
            numberOfWords++;
        }
    }
    // Closing file and returning true
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Just returning an int I've counted in load(). The key is that it has to be declared outside of load in order for size to return it
    // Otherwise it will be an undeclared in for size()
    return numberOfWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Using a for loop to go through all the arrays of the hash table
    for (int i = 0; i < N ; i++)
    {
        // Using a while table to go through each linked list of the hash table
        // When an array of the list will point to nothing than it means we have gone through each one of them
        while (table[i] != NULL)
        {
            // Setting a trav node to point at whatever table is pointing to next (?)
            node *tmp = table[i] -> next;
            // Freeing tbale (?)
            free(table[i]);
            // Setting table to tmp (?)
            // Took this code structure from course. Have to understand it better. 
            table[i] = tmp;
        }
    }
    return true;
}
