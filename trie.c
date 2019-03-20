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

trieNode *findPrefix(trieNode *base, const char *string, int *depth)
{
    trieNode *current = base;
    if (current->childNumber == 0)
    {
        return current;
    }
    int length = 0;

    for (int i = 0; i < current->childNumber; i++)
    {
        if (current->children[i]->letter != string[length])
            continue;
        current = current->children[i];
        length++;
        i = 0;
    }

    *depth = length;
    return current;
}

trieNode *newTrieNode(char letter, bool endOfWord)
{
    trieNode *new = malloc(sizeof(trieNode));
    new->letter = letter;
    if (endOfWord)
    {
        new->endOfWord = true;
        new->childNumber = 0;
        new->children = NULL;
    } else
    {
        new->endOfWord = false;
        new->childNumber = 1;
        new->children = malloc(sizeof(trieNode *));
    }

    return new;
}

trieNode *addSuffix(char *string)
{
    if (string[0] == '\0')
        return NULL;
    bool isLast = (string[1] == '\0') ? true : false; // False iff string[1] is null (there are no more letters)
    char c = string[0];

    trieNode *new = newTrieNode(c, isLast);
    if (!isLast)
    {
        new->children[0] = addSuffix(string + 1);
        return new;
    }
}

void displayTrie(trieNode *root, char *str, int level, int number)
{
    if (number > 0 && printed >= number)
        return;
    char letter = root->letter;
    if (root->endOfWord)
    {
        str[level] = letter;
        str[level + 1] = '\0';
        puts(str + 1);
        printed++;

    }
    for (int i = 0; i < root->childNumber; i++)
    {
        str[level] = letter;
        if (level == 0)
            str[0] = ' ';
        displayTrie(root->children[i], str, level + 1, number);
    }
}

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
        if (current->children[i]->letter != string[length])
            continue;
        current = current->children[i];
        length++;
        i = 0;
    }

    *depth = length;
    return current;
}

void insertTrieNode(trieNode *base, char *string)
{
    int prefixLength = 0;
    trieNode *prefix = findPrefix(base, string, &prefixLength);

    if (prefixLength == strlen(string))
    {
        prefix->endOfWord = true;
        return;
    }

    prefix->childNumber += 1; // Update number of children

    trieNode **newChildren = realloc(prefix->children,
                                      sizeof(trieNode *) * prefix->childNumber); // Allocate space for the new one

    prefix->children = newChildren;
    prefix->children[prefix->childNumber - 1] = addSuffix(string + prefixLength); // Add the rest of the nodes to it
}



