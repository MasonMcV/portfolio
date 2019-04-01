//
// Created by mason on 3/5/19.
//
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

#include "mybool.h"
#include "trie.h"

int printed;

char myLower(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
        c = (char) (c + 32);
    return c;
}

// Go through all of the nodes till a null is found or the end of the string is found
trieNode *findPrefix(trieNode *base, const char *string, int *depth)
{
    trieNode *current = base;
    if (current->childNumber == 0)
    {
        return current;
    }
    int length = 0;

    for (int i = 0; i < current->childNumber;)
    {
        if (current->children[i]->letter != myLower(string[length]))
        {
            i++;
            continue;
        }
        current = current->children[i];
        length++;
        i = 0;
    }

    *depth = length;
    return current;
}

// Add a new node with memory allocated based on position in the word.
trieNode *newTrieNode(char letter, bool endOfWord, MOVIE *movie)
{
    trieNode *new = malloc(sizeof(trieNode));
    int c;
    if (isalpha(letter))
        c = tolower(letter);
    else
        c = letter;
    new->letter = myLower(letter);
    if (endOfWord)
    {
        new->endOfWord = true;
        new->childNumber = 0;
        new->children = NULL;
        new->movieNumber = 1;
        new->movie = calloc(sizeof(MOVIE *), 1);
        new->movie[0] = movie;
    } else
    {
        new->endOfWord = false;
        new->childNumber = 1;
        new->children = malloc(sizeof(trieNode *));
        new->movieNumber = 0;
        new->movie = NULL;
    }

    return new;
}

// Add child nodes in position 0 till the end of the word.
trieNode *addSuffix(char *string, MOVIE *movie)
{
    if (string[0] == '\0')
        return NULL;
    bool isLast = (string[1] == '\0') ? true : false; // False iff string[1] is null (there are no more letters)
    char c = string[0];

    trieNode *new = newTrieNode(c, isLast, movie);
    if (!isLast)
    {
        new->children[0] = addSuffix(string + 1, movie);
        return new;
    }
}

// Display number or less end of word nodes descending from the current node
void displayTrie(trieNode *root, char *str, int number)
{
    if (number > 0 && printed >= number)
        return;
    if (root->endOfWord)
    {
        for (int i = 0; i < root->movieNumber; i++)
        {
            MOVIE *movie = root->movie[i];
            printf("%s, %d. %d, %s", movie->title, movie->year, movie->runtime, movie->genres);
            printed++;
            if (number > 0 && printed >= number)
                return;
        }
    }
    for (int i = 0; i < root->childNumber; i++)
    {
        displayTrie(root->children[i], str, number);
    }
}

// Same as displayTrie, but pust is in list to be printed with ncurses
void getMovieList(trieNode *root, int number, MOVIE **list)
{
    if (number > 0 && printed >= number)
        return;
    if (root->endOfWord)
    {
        for (int i = 0; i < root->movieNumber; i++)
        {
            list[printed] = root->movie[i];
            printed++;
            if (number > 0 && printed >= number)
                return;
        }
    }
    for (int i = 0; i < root->childNumber; i++)
        getMovieList(root->children[i], number, list);
}

// Handles the main logic of adding a record to the trie
void insertTrieNode(trieNode *base, char *string, MOVIE *movie)
{
    int prefixLength = 0;
    trieNode *prefix = findPrefix(base, string, &prefixLength);

    if (prefixLength == strlen(string)) // the record is already in the trie - add a new record in movie list
    {
        prefix->endOfWord = true;
        prefix->movieNumber++;
        prefix->movie = realloc(prefix->movie, sizeof(MOVIE *) * prefix->movieNumber);
        prefix->movie[prefix->movieNumber - 1] = movie;
        return;
    }

    prefix->childNumber += 1; // Update number of children

    trieNode **newChildren = realloc(prefix->children,
                                     sizeof(trieNode *) * prefix->childNumber); // Allocate space for the new one

    prefix->children = newChildren;
    prefix->children[prefix->childNumber - 1] = addSuffix(string + prefixLength,
                                                          movie); // Add the rest of the nodes to it
}

