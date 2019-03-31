//
// Created by mason on 3/26/19.
//

#include "nCursesHandler.h"
#include "movie.h"
#include "fileio.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

typedef struct WIDGET
{
    WINDOW *window;
    int x;
    int y;
} WIDGET;

int selected = 0;

WIDGET home;
WINDOW *search;
WINDOW *dialog;
WINDOW *journal;

char *welcomeText = "Welcome to iMovieSearch";
char *instructions1 = "Press esc to Exit";
char *instructions2 = "Press tab to switch between search and display";

void drawBox(WINDOW *window, char *title);

void newScreen()
{
    home.window = initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    raw();
    keypad(home.window, TRUE);
    noecho();
    //curs_set(0);
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    home.x = x;
    home.y = y;
    mvprintw(0, (int) (x - strlen(welcomeText)) / 2, welcomeText);
    mvprintw(1, 0, "Press esc to exit");
    mvprintw(2, 0, "Press tab to switch between search and display");

    // Arg Order           H   W  Y  X
    search = newwin(24, x, 5, 0);
    dialog = newwin(6, 60, 20, x / 2 - 30);
    journal = newwin(1000, x, 5, 0); // Large so the movies fill teh whole screen instead of cutting off at 20

    
    // Set up the initial search window
    box(search, 0, 0);
    for (int j = 1; j < x - 1; j++)
        mvwaddch(search, 2, j, '-');
    refresh();
    box(search, 0, 0);
    wattron(search, COLOR_PAIR(1));
    mvwprintw(search, 0, 0, "Search:");
    wattroff(search, COLOR_PAIR(1));
    wmove(search, 1, 1);
    wrefresh(search);

    box(dialog, 0, 0);
    wattron(dialog, COLOR_PAIR(1));
    mvwprintw(dialog, 0, 0, "Input Data:");
    wattroff(dialog, COLOR_PAIR(1));
    wmove(dialog, 1, 1);
    //wrefresh(dialog);
}

char handleInput()
{
    int i = getch();
    //printw("%d", i);
    if (i == 27) // Escape
        return '\0';
    return i;
}

void newSearch(char *string, MOVIE **movieData, int number, int selected)
{
    WINDOW *window = search;
    wclear(window);
    printMovies(movieData, number, selected);
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 0, "Search:");
    wattroff(window, COLOR_PAIR(1));
    for (int j = 1; j < home.x - 1; j++)
    {
        mvwaddch(window, 2, j, '-');
    }
    mvwprintw(window, 1, 1, string);
    wmove(window, 1, (int) strlen(string) + 1);
    wrefresh(window);
}

void showSearch()
{
    drawBox(search, "Search");
}

void printMovies(MOVIE **movieData, int number, int selected)
{
    for (int i = 0; i < number; i++)
    {
        MOVIE *movie = movieData[i];
        if (movie == NULL)
            break;
        if (selected == i)
            wattron(search, A_STANDOUT);
        mvwprintw(search, i + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime,
                  movie->genres);
        if (selected == i)
            wattroff(search, A_STANDOUT);
    }
    wrefresh(search);
}

void showInputDialog()
{
    WINDOW *window = dialog;
    drawBox(window, "Input Data: ");
    mvwprintw(window, 2, 1, "Input Medium (DVD/Blueray/Digital)");
    mvwprintw(window, 2, 40, "Date Aquired");
    wmove(window, 1, 1);
    wrefresh(window);
    refresh();
}

void journalCallback(char *str, int i)
{
    if(i == selected)
        wattron(journal, A_STANDOUT);
    mvwprintw(journal, i+1, 1, str);
    if(i == selected)
        wattroff(journal, A_STANDOUT);
}

int newJournal(char *name, int numSelected)
{
    selected = numSelected;
    drawBox(journal, "Journal");
    int numEntries = getFileWords(name, journalCallback);
    move(0, home.x); // Out of sight
    wrefresh(journal);
    return numEntries;
}

void printInputText(char *meduim, char *date)
{
    wclear(dialog);
    drawBox(dialog, "Input Data: ");
    mvwprintw(dialog, 2, 1, "Input Medium (DVD/Blueray/Digital)");
    mvwprintw(dialog, 2, 40, "Date Aquired");
    //for (int i = 1; i > 59; i++)
    mvwprintw(dialog, 3, 1, meduim);
    mvwprintw(dialog, 3, 40, date);
    wmove(dialog, 3, 1);
    wrefresh(dialog);
}


void endCurses()
{
    endwin();
}

void drawBox(WINDOW *window, char *title)
{
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 0, title);
    wattroff(window, COLOR_PAIR(1));
    wrefresh(window);
}
