//
// Created by mason on 3/12/19.
//

#ifndef PORTFOLIO_MOVIE_H
#define PORTFOLIO_MOVIE_H

#include "mybool.h"

typedef struct MOVIE
{
    char *title;
    bool isAdult;
    int year;
    int runtime;
    char *genres;
} MOVIE;



#endif //PORTFOLIO_MOVIE_H
