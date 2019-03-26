#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "mybool.h"
#include "movie.h"
#include "fileio.h"


#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <ncurses.h>
#include <ctype.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

void getTrieStrings(trieNode *root, WINDOW *win, int number);

void ncursesDisplayTrie(trieNode *root, WINDOW *win, int number);

int countNodes(trieNode *root)
{
    if (root->children == NULL)
    {
        return 1;
    }
    int number = 1;
    for (int i = 0; i < root->childNumber; i++)
    {
        number += countNodes(root->children[i]);
    }
    return number;
}

int printed;

int main()
{
    // Get the number of letters / words / lines in the movie.tsv file
    /*FILE *shell;
    char *command = "wc -l ../wordsdata.tsv";
    static int WORD_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &WORD_COUNT);
    pclose(shell);
    printf("%d Letters\n\n", WORD_COUNT);*/

    srand(time(0));

    MOVIE **movieList = calloc(sizeof(MOVIE *), 1);

    trieNode base = {
            .letter = '\0',
            .endOfWord = false,
            .childNumber = 0,
            .children = NULL
    };
    double startTime = get_time();
    readFileIn(movieList, &base);
    double endTime = get_time();
    //printf("Building took: %lf\n", endTime - startTime);

    startTime = get_time();
    int nodes = countNodes(&base);
    endTime = get_time();
    //printf("Counting took: %lf, There are %d nodes\n", endTime - startTime);

    printf("There are %d nodes\n", countNodes(&base));

    char str[409];

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
    box(win, 0, 0);
    for (int j = 1; j < x - 1; j++)
        mvwaddch(win, 2, j, '-');
    mvprintw(11, x / 2 - 12, "Press Any Key to Start");
    mvprintw(14, x / 2 - 20, "At any time, press esc then 'q' to exit");
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
            if (strlen(string) < 400)
                string[i++] = (char) ch;
        }
        wclear(win);
        attron(A_BOLD);
        printed = 0;
        int length;
        trieNode *node = findPrefix(&base, string, &length);
        mvprintw(25, 25, "The char at the root is : %c", node->letter);
        //getTrieStrings(node, win, 20);
        ncursesDisplayTrie(node, win, 20);

        char newString[420] = "A ";
        strcat(newString, string);
        node = findPrefix(&base, newString, &length);
        ncursesDisplayTrie(node, win, 20);

        strcpy(newString, "The ");
        strcat(newString, string);
        node = findPrefix(&base, newString, &length);
        ncursesDisplayTrie(node, win, 20);
        //free(node);
        mvwprintw(win, 1, 1, "%s\n", string);
        attroff(A_BOLD);
        for (int j = 0; j < x - 1; j++)
            mvwaddch(win, 2, j, '-');
        box(win, 0, 0);
        wrefresh(win);
    }
    endwin();//*/

    /*char userInput[409] = {0};

    printf("\n\nEnter Search: ");
    while (strcmp(userInput, "DONE") !=0)
    {
        fgets(userInput, 400, stdin);

        int length = 0;
        printed = 0;
        double startTime = get_time();
        trieNode* node = findPrefix(&base, userInput, &length);
        double endTime = get_time();
        //printf("%d", (int) node);
        displayTrie(node, str, 20);
        double finalTime = get_time();
        printf("\n\nSearch took: %lf\n", endTime - startTime);
        printf("Altogether took: %lf", finalTime - startTime);
        userInput[0] = '\0';
        printf("\n\nEnter Next Search: ");
    }//*/
    exit(0);
}

void ncursesDisplayTrie(trieNode *root, WINDOW *win, int number)
{
    if (number > 0 && printed >= number)
        return;
    if (root->endOfWord)
    {
        for (int i = 0; i < root->movieNumber; i++)
        {
            MOVIE *movie = root->movie[i];
            mvwprintw(win, printed + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime, movie->genres);
            printed++;
            if (number > 0 && printed >= number)
                return;
        }
    }
    //if(root->childNumber > 0)
    for (int i = 0; i < root->childNumber; i++)
        ncursesDisplayTrie(root->children[i], win, number);
    //for (int i = 0; i < root->childNumber; i++)
    //{

    //}
}

void getTrieStrings(trieNode *root, WINDOW *win, int number)
{
    MOVIE *results[number];
    int resultNum = 0;

    if (root->childNumber == 0)
    {
        if (root->movieNumber == 0)
            return;
        for (int i = 0; i < root->movieNumber; i++)
        {
            MOVIE *movie = root->movie[i];
            mvwprintw(win, printed + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime, movie->genres);
            printed++;
            if (printed > number)
                return;
        }
    }

    while (resultNum < number)
    {
        if (root->childNumber == 0)
            continue;
        trieNode *base = root->children[rand() % root->childNumber];
        while (base != NULL)
        {
            if (base->endOfWord)
            {
                for (int i = 0; i < root->movieNumber; i++)
                {
                    MOVIE *movie = root->movie[i];
                    mvwprintw(win, printed + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime,
                              movie->genres);
                    printed++;
                    if (printed > number)
                        return;
                }
            }
            if (base->childNumber == 0)
                continue;
            base = base->children[rand() % base->childNumber];
        }
    }
    /*for (int i = 0; i < number; i++)
    {
        MOVIE *movie = results[i];
        mvwprintw(win, printed + 3, 1, "%s, %d. %d, %s", movie->title, movie->year, movie->runtime, movie->genres);
        printed++;
    }*/
}
