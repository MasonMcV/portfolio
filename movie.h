//
// Created by mason on 3/12/19.
//

#ifndef PORTFOLIO_MOVIE_H
#define PORTFOLIO_MOVIE_H

#include <stdbool.h>

typedef struct MOVIE
{
    int id;
    char tconst[10];
    char titleType[10];
    char primaryTitle[100];
    char originalTitle[100];
    bool isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    char genres[41];
} MOVIE;

#endif //PORTFOLIO_MOVIE_H
