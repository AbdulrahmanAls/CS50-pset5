/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define LENGTH 45
#define HASHSIZE 50
 
unsigned int sizeLoad = 0 ;

typedef struct node {
    char words[LENGTH + 1];
    struct node* next ; 
} node ;

node* hashtable[50];


// the hash function from https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}


bool check(const char *word)
{    
    char words[LENGTH + 1]; 
    strcpy(words , word);
    
    int hashval = hash(words);

    for(int i = 0 ; words[i] != '\0' ; i++)
        {
            if(isupper(words[i]))
            {
                tolower(words[i]);
            }
        }
        
        node* cursor = hashtable[hashval];
        
        while(cursor != NULL)
        {
            if(strcmp(cursor->words, word) == 0)
            {
                return true; 
            }
            
            cursor = cursor-> next; 
        }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    int hashval ;
    FILE *fp = fopen(dictionary,"r");
    
    if (fp == NULL)
    {
        printf("Can't open the file. \n");
        return 0 ;
    }
    
    char word[LENGTH + 1]; 
    
    while (fscanf(fp,"%s\n",word) != EOF)
    {
        node* NewNode = (node *) malloc(sizeof(node));
        
        if (NewNode == NULL)
        {
            unload();
            return false;
        }
        
        NewNode->next = NULL;
        
        for(int i = 0 ; word[i] != '\n' ; i++)
        {
            if(isupper(word[i]))
            {
                tolower(word[i]);
            }
        }
        strcpy(NewNode->words, word);
        
        hashval = hash(word);
        
        if(hashtable[hashval] == NULL)
        {
            hashtable[hashval] = NewNode ;
            
        }else {
            
            NewNode->next = hashtable[hashval];
            hashtable[hashval] = NewNode ; 
    
        }
        sizeLoad++; 
    }
    fclose(fp); 
    return true ;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   
    return sizeLoad;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    
    for(int i = 0 ; i <= HASHSIZE ; i++)
    {
        node* cursor = hashtable[i];
        node* temp ; 
        while(cursor != NULL)
        {
            temp = cursor ; 
            cursor = cursor -> next ;
            free(temp);
        }
    }
    return true;
}
