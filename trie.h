//
// Created by mason on 3/5/19.
//

#ifndef PORTFOLIO_TRIE_H
#define PORTFOLIO_TRIE_H

#include <stdbool.h>

typedef struct trieNode
{
    char letter;
    bool endOfWord;
    struct trieNode *children[49];
} trieNode;

typedef struct dafsaNode
{
    char letter;
    bool endOfWord;
    int childNumber;
    struct dafsaNode **children;
} dafsaNode;



void insertTrieNode(trieNode *base, char *string);


void displayTrie(trieNode *root, char *str, int level);

void insertDAFSANode(struct dafsaNode *base, char* string);

void displayDAFSA(dafsaNode *root, char *str, int level);


#endif //PORTFOLIO_TRIE_H
