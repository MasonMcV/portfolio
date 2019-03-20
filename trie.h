//
// Created by mason on 3/5/19.
//

#ifndef PORTFOLIO_TRIE_H
#define PORTFOLIO_TRIE_H

#include "mybool.h"

typedef struct trieNode
{
    char letter;
    bool endOfWord;
    int childNumber;
    //MOVIE *data;
    struct trieNode **children;
} trieNode;


void insertTrieNode(struct trieNode *base, char *string);

void displayTrie(trieNode *root, char *str, int level, int number);

trieNode *searchTrie(trieNode *base, const char *string, int *depth);

#endif //PORTFOLIO_TRIE_H
