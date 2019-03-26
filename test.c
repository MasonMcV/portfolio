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

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    // Arg Order         H   W  Y  X
    WINDOW *win = newwin(22, x, 0, 0);
    /*box(win, 0, 0);
    for (int j = 1; j < n - 1; j++)
        mvwaddch(win, 2, j, '-');*/
    mvprintw(11, x/2-12, "Press Any Key to Start");
    mvprintw(14, x/2-20, "At any time, press esc then 'q' to exit");
    wrefresh(win);
    refresh();
    getch();
    for (int j = 0; j < x - 1; j++)
        mvwaddch(win, 2, j, '-');
    box(win, 0, 0);
    wrefresh(win);
    int i = 0;
    while (true)
    {
        ch = getch();
        if (ch == 27)
            break;
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
        attroff(A_BOLD);
        for (int j = 0; j < x - 1; j++)
            mvwaddch(win, 2, j, '-');
        box(win, 0, 0);
        wrefresh(win);
    }
    endwin();
    return 0;
}