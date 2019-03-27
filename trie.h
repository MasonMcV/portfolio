//
// Created by mason on 3/5/19.
//

#ifndef PORTFOLIO_TRIE_H
#define PORTFOLIO_TRIE_H

#include "mybool.h"
#include "movie.h"



typedef struct trieNode
{
    char letter;
    bool endOfWord;
    int childNumber;
    int movieNumber;
    char childrenLetters[100];
    MOVIE **movie;
    struct trieNode **children;
} trieNode;


void insertTrieNode(struct trieNode *base, char *string, MOVIE *movie);

void displayTrie(trieNode *root, char *str, int number);

void getMovieList(trieNode *root, int number, MOVIE **list);

trieNode *findPrefix(trieNode *base, const char *string, int *depth);

#endif //PORTFOLIO_TRIE_H
