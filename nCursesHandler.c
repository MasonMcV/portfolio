//
// Created by mason on 3/26/19.
//

#include "nCursesHandler.h"
#include "movie.h"
#include <ncurses.h>
#include <string.h>

typedef struct WIDGET
{
    WINDOW *window;
    bool isSelected;
    int x;
    int y;
} WIDGET;

int selected = 0;

WIDGET home;
WIDGET search;
WINDOW dialog;
WINDOW journal;

void newScreen()
{
    home.window = initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    raw();
    keypad(home.window, TRUE);
    noecho();
    //curs_set(0);
    search.x = getmaxx(stdscr);
    search.y = getmaxy(stdscr);

    // Arg Order           H   W  Y  X
    search.window = newwin(24, search.x, 5, 0);

    box(search.window, 0, 0);
    for (int j = 1; j < search.x - 1; j++)
        mvwaddch(search.window, 2, j, '-');
    mvprintw(0, 0, "Press esc to exit");
    refresh();
    box(search.window, 0, 0);
    wattron(search.window, COLOR_PAIR(1));
    mvwprintw(search.window, 0, 0, "Search:");
    wattroff(search.window, COLOR_PAIR(1));
    wmove(search.window, 1, 1);
    wrefresh(search.window);
}

char handleInput()
{
    int i = getch();
    //printw("%d", i);
    if (i == 27) // Escape
        return '\0';
    return i;
}

void newSearch(char *string, MOVIE **movieData, int number)
{
    wclear(search.window);
    printMovies(movieData, number);
    box(search.window, 0, 0);
    wattron(search.window, COLOR_PAIR(1));
    mvwprintw(search.window, 0, 0, "Search:");
    wattroff(search.window, COLOR_PAIR(1));
    for (int j = 1; j < search.x - 1; j++)
        mvwaddch(search.window, 2, j, '-');
    mvwprintw(search.window, 1, 1, string);
    wmove(search.window, 1, (int) strlen(string) + 1);
    wrefresh(search.window);
}

void printMovies(MOVIE **movieData, int number)
{
    for (int i = 0; i < number; i++)
    {
        MOVIE *movie = movieData[i];
        if (movie == NULL)
            break;
        if(selected == i)
            wattron(search.window, A_STANDOUT);
        mvwprintw(search.window, i + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime,
                  movie->genres);
        if(selected == i)
            wattroff(search.window, A_STANDOUT);
    }
    wrefresh(search.window);
}

void endCurses()
{
    endwin();
}