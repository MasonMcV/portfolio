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

// Prototype for drawBox found below
void drawBox(WINDOW *window, char *title);

// Initiate the screen and set up the first search function
void newScreen()
{
    home.window = initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    raw();
    keypad(home.window, TRUE);
    noecho();
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    home.x = x;
    home.y = y;
    mvprintw(0, (int) (x - strlen(welcomeText)) / 2, welcomeText);
    mvprintw(1, 0, "Press esc to exit");
    mvprintw(2, 0, "Press tab to switch between search and display");
    mvprintw(3, 0, "Arrow Keys to cycle through lists");
    // Arg Order           H   W  Y  X
    search = newwin(24, x, 5, 0);
    dialog = newwin(6, 60, 10, x / 2 - 30);
    journal = newwin(1000, x, 5, 0); // Large so the movies fill the whole screen instead of cutting off at 20


    // Set up the initial search window
    box(search, 0, 0);
    for (int j = 1; j < x - 1; j++)
        mvwaddch(search, 2, j, '-');
    refresh();
    drawBox(search, "Search: - Press Enter to add entry");
    wrefresh(search);
}

// Handles input for the other functions.  Returns only ints, and NCURSES MACROS wont  work in other files
char handleInput()
{
    int i = getch();
    if (i == 27) // Escape
        return '\0';
    return i;
}

// Redraws the search window after a new search is initiated (letter is typed)
void newSearch(char *string, MOVIE **movieData, int number, int selected)
{
    WINDOW *window = search;
    wclear(window);
    printMovies(movieData, number, selected);
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 0, "Search: - Press Enter to add entry");
    wattroff(window, COLOR_PAIR(1));
    for (int j = 1; j < home.x - 1; j++)
    {
        mvwaddch(window, 2, j, '-');
    }
    mvwprintw(window, 1, 1, string);
    wmove(window, 1, (int) strlen(string) + 1);
    wrefresh(window);
}

// Show the search box - ready for input
void showSearch()
{
    drawBox(search, "Search: - Press Enter to add entry");
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

// Callback function for printing the journal
void journalCallback(char *str, int i)
{
    if (i == selected)
        wattron(journal, A_STANDOUT);
    mvwprintw(journal, i + 1, 1, str);
    if (i == selected)
        wattroff(journal, A_STANDOUT);
}

// Displays the journal from file
int newJournal(char *name, int numSelected)
{
    wclear(journal);
    selected = numSelected;
    drawBox(journal, "Journal");
    int numEntries = getFileWords(name, journalCallback);
    wmove(journal, numSelected+1, 1);
    wrefresh(journal);
    return numEntries;
}

// Prints the input dialog - refresh every letter added
void printInputText(char *medium, char *date, int field)
{
    wclear(dialog);
    drawBox(dialog, "Input Data: Ent: Accept - Del: Cancel - Tab - Switch");
    mvwprintw(dialog, 2, 1, "Input Medium (DVD/Blueray/Digital)");
    mvwprintw(dialog, 2, 40, "Date Aquired");
    //for (int i = 1; i > 59; i++)
    mvwprintw(dialog, 3, 1, medium);
    mvwprintw(dialog, 3, 40, date);
    int movePosition = (int) (field ? 40 + strlen(date) : strlen(medium) + 1);
    wmove(dialog, 3, movePosition);
    wrefresh(dialog);
}

// Exits the NCURSES safely
void endCurses()
{
    endwin();
}

// draws a box around the window with title
void drawBox(WINDOW *window, char *title)
{
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 0, 0, title);
    wattroff(window, COLOR_PAIR(1));
    wmove(window, 1, 1);
    wrefresh(window);
}
