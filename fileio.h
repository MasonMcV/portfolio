//
// Created by mason on 3/12/19.
//

#ifndef PORTFOLIO_FILEIO_H
#define PORTFOLIO_FILEIO_H

#include "movie.h"
#include "trie.h"

typedef struct logEntry
{
    char *title;
    int year;
    int runtime;
    char *genres;
    char *medium;
    char datePurchased;
} logEntry;

void readFileIn(trieNode *base);

void addToUserFile(char *name, MOVIE *movie, char *medium, char *date);

int getFileWords(char *name, void (*callback)(char *, int));

void deleteRecord(char *name, int number);

void updateRecord(char *name, int number, char *medium, char *date);



#endif //PORTFOLIO_FILEIO_H
