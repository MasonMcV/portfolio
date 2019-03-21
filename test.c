//
// Created by mason on 3/13/19.
//

// Inspiration from https://pdfs.semanticscholar.org/47d4/e80971ef43eebe3f63413abeefd19ec5ea2a.pdf
// Better quality and better info at http://aclweb.org/anthology/J00-1002
//
// Also look at http://www.cs.cmu.edu/afs/cs/academic/class/15451-s06/www/lectures/scrabble.pdf

#include <stdio.h>
#include "mybool.h"
#include <memory.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

#include "movie.h"
#include "fileio.h"

int main()
{
    int ch;
    char string[400] = {0};

    /*printw("Please resize Window to full screen. \n\n");*/

    initscr();
    printw("Press Any Key to Start");
    refresh();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int n = getmaxx(stdscr);
    //                   H   W   Y   X
    WINDOW *win = newwin(22, n, 0, 0);
    /*box(win, 0, 0);
    for (int j = 1; j < n - 1; j++)
        mvwaddch(win, 2, j, '-');*/
    wrefresh(win);
    ch = getchar();
    int i = 0;
    while (ch != 27)
    {
        if (ch == KEY_BACKSPACE)
        {
            if (strlen(string) > 0)
                string[--i] = '\0';
        } else if (ch == 10)
        {
            for (int j = 0; j < i; j++)
                string[j] = '\0';
            i = 0;
        } else
        {
            string[i++] = (char) ch;
        }
        wclear(win);
        attron(A_BOLD);
        mvwprintw(win, 1, 1, "%s\n", string);
        for (int j = 0; j < n - 1; j++)
            mvwaddch(win, 2, j, '-');
        attroff(A_BOLD);
        box(win, 0, 0);
        wrefresh(win);
        ch = getch();
        if (ch == 27)
            break;
    }
    endwin();
    return 0;
}