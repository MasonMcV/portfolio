//
// Created by mason on 3/26/19.
//

#ifndef PORTFOLIO_NCURSESHANDLER_H
#define PORTFOLIO_NCURSESHANDLER_H

#include "movie.h"

void newScreen();

char handleInput();

void newSearch(char *string, MOVIE **movieData, int number, int selected);

void showSearch();

void printMovies(MOVIE **movieData, int number, int selected);

void showInputDialog();

int newJournal(char *name, int numSelected);

void printInputText(char* meduim, char* date);

void endCurses();

#endif //PORTFOLIO_NCURSESHANDLER_H
