//
// Created by mason on 3/5/19.
//
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

#include "trie.h"
#include "lettermap.h"

trieNode *getNewNode()
{
    trieNode *node = (trieNode *) calloc(sizeof(trieNode), 1);
    node->endOfWord = false;

    for (int i = 0; i < 48; i++)
        node->children[i] = NULL;
    return node;
}


void insertTrieNode(trieNode *base, char *string)
{
    trieNode *current = base;
    int letterMap[strlen(string)];
    getMapping(string, letterMap);
    for (int i = 0; string[i] != '\0'; i++)
    {
        //int letter = getLocationForChar(string[i]);
        int letter = letterMap[i];
        if (current->children[letter] == NULL)
        {
            current->children[letter] = getNewNode();
        }
        current->children[letter]->letter = (char) toupper(string[i]);
        current = current->children[letter];
    }
    current->endOfWord = true;
}

dafsaNode *findPrefix(dafsaNode *base, const char *string, int *depth)
{
    dafsaNode *current = base;
    dafsaNode *next;
    if (current->childNumber == 0)
    {
        return current;
    }
    int length = 0;

    for (int i = 0; i < current->childNumber; i++)
    {
        /*if(length > strlen(string))
            break;*/
        if (current->children[i]->letter != string[length])
            continue;
        current = current->children[i];
        length++;
        i = 0;
        // Search the next level
        /*if (current->children[i]->letter == string[0])
            return findPrefix(current, string++, (*depth)++);*/
        /*next = current->children[i];
        while (next->letter == string[0])
        {
            string++;
            if (next->children == NULL)
            {
                if (next->letter == string[0])
                {
                    length++;
                    current = next;
                }
                break;
            }
            length++;
            current = next;

            next = next->children[i];
        }*/
    }

    *depth = length;
    return current;
}

dafsaNode *newdafsaNode(char letter, bool endOfWord)
{
    dafsaNode *new = malloc(sizeof(dafsaNode));
    new->letter = letter;
    if (endOfWord)
    {
        new->endOfWord = true;
        new->childNumber = 0;
    } else
    {
        new->endOfWord = false;
        new->childNumber = 1;
        new->children = malloc(sizeof(dafsaNode *));
    }

    return new;
}

void addSuffix(dafsaNode *current, int number, char *string)
{
    current->children[number] = newdafsaNode(*string, (*(string + 1) == 0));
    printf("%ld, %c  ", (long) current, *string);
    string++;
    dafsaNode *prev;
    prev = current->children[number];
    while (*string != '\0')
    {
        dafsaNode *new = newdafsaNode(*string, (*(string + 1) == 0));
        printf("%ld, %c  ", (long) new, *string);
        prev->children[0] = new;
        prev = prev->children[0];
        string++;
    }
    printf("\n");
}

void displayDAFSA(dafsaNode *root, char *str, int level)
{
    if (root->endOfWord)
    {
        str[level] = root->letter;
        str[level + 1] = '\0';
        printf("%s\n", str);
    }
    for (int i = 0; i < root->childNumber; i++)
    {
        if (level == 0)
        {
            str[0] = ' ';
            displayDAFSA(root->children[i], str, level + 1);
        }
        str[level] = root->letter;
        displayDAFSA(root->children[i], str, level + 1);
    }
}

void insertDAFSANode(dafsaNode *base, char *string)
{
    int prefixLength = 0;
    dafsaNode *prefix = findPrefix(base, string, &prefixLength);



    // Add the first child and all subsequent letters in that word.
    /*if (prefix->children == NULL)
    {
        prefix->children = malloc(sizeof(dafsaNode *));
        prefix->childNumber = 1;
        dafsaNode *current = prefix;
        char *stringPosition = string + prefixLength;
        while (stringPosition[0] != '\0')
        {
            dafsaNode *new = newdafsaNode(stringPosition[0], (stringPosition[1] == 0));
            current->children[0] = new;
            current = current->children[0];
            stringPosition++;
        }
        return;
    }*/

    if (prefixLength == strlen(string))
    {
        prefix->endOfWord = true;
        return;
    }


    prefix->childNumber += 1; // Update number of children

    prefix->children = realloc(prefix->children,
                               sizeof(dafsaNode *) * prefix->childNumber); // Allocate space for the new one


    addSuffix(prefix, prefix->childNumber - 1, string + prefixLength); // Add the rest of the nodes to it

    /*for (int i = 0; i < prefix->childNumber; i++)
    {
        //printf("%d, %c\n", i, prefix->children[i]->letter);
        char str[400] = {0};
        displayDAFSA(prefix->children[i], str, 0);

    }
    printf("\n");*/
}

/*
 * FOR WORD IN WORDS
 *  node* = find_prefix( word )             ; returns pointer to state
 *  ?? lastState = path to prefix
 *  node* firstState = the first state that has a confluence or null if none
 *  suffix = the rest of the word
 *  if firstState = null
 *      if (! has_children)
 *          node* add_suffix( word )
 *          continue;
 *      else:
 *          for each child
 *              find portion that continues after change
 *              restructure the tree
 */

void displayTrie(trieNode *root, char *str, int level)
{
    if (root->endOfWord)
    {
        str[level] = '\0';
        puts(str);
    }
    for (int i = 0; i < 48; i++)
    {
        if (root->children[i])
        {
            str[level] = getCharFromMapping(i);
            displayTrie(root->children[i], str, level + 1);
        }
    }
}


