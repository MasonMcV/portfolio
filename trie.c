//
// Created by mason on 3/5/19.
//
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

#include "mybool.h"
#include "trie.h"
#include "lettermap.h"

int printed;

char myLower(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
        c = (char) (c + 32);
    return c;
}

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

trieNode *addSuffix(char *string, MOVIE *movie)
{
    if (string[0] == '\0')
        return NULL;
    bool isLast = (string[1] == '\0') ? true : false; // False iff string[1] is null (there are no more letters)
    char c = string[0];

    trieNode *new = newTrieNode(c, isLast, movie);
    if (!isLast)
    {
        new->childrenLetters[0] = *(string + 1);
        new->children[0] = addSuffix(string + 1, movie);
        return new;
    }
}

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

/*int countNodes(trieNode *root)
{
    if (root->children == NULL)
    {
        return 1;
    }
    int number = 0;
    for (int i = 0; i < root->childNumber; i++)
    {
        number += countNodes(root->children[i]);
    }
    return number;
}*/

trieNode *searchTrie(trieNode *base, const char *string, int *depth)
{
    trieNode *current = base;
    if (current->childNumber == 0)
    {
        return current;
    }
    int length = 0;

    for (int i = 0; i < current->childNumber; i++)
    {
        if (current->children[i]->letter != myLower(string[length]))
            continue;
        current = current->children[i];
        length++;
        i = 0;
    }

    *depth = length;
    return current;
}

void insertTrieNode(trieNode *base, char *string, MOVIE *movie)
{
    int prefixLength = 0;
    trieNode *prefix = findPrefix(base, string, &prefixLength);

    if (prefixLength == strlen(string))
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
    prefix->childrenLetters[prefix->childNumber - 1] = *(string + prefixLength);
    prefix->children[prefix->childNumber - 1] = addSuffix(string + prefixLength,
                                                          movie); // Add the rest of the nodes to it
}



