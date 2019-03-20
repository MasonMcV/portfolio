//
// Created by mason on 3/5/19.
//

#ifndef PORTFOLIO_TRIE_H
#define PORTFOLIO_TRIE_H

#include "mybool.h"

typedef struct dafsaNode
{
    char letter;
    bool endOfWord;
    int childNumber;
    struct dafsaNode **children;
} dafsaNode;


void insertDAFSANode(struct dafsaNode *base, char* string);

void displayDAFSA(dafsaNode *root, char *str, int level, int number);

dafsaNode *searchDAFSA(dafsaNode *base, const char *string, int *depth);

#endif //PORTFOLIO_TRIE_H
