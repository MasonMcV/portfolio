#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <ctype.h>

#include "mybool.h"
#include "movie.h"
#include "fileio.h"
#include "nCursesHandler.h"

#include <ncurses.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

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

typedef enum STATE
{
    SEARCH,
    INPUT,
    JOURNAL
} STATE;

int main()
{
    char fileName[400] = {0};
    puts("Enter your name: ");
    scanf("%s", fileName);

    puts("Welcome, Loading now...");

    srand(time(0));

    MOVIE **movieList = calloc(sizeof(MOVIE *), 1);

    trieNode base = {
            .letter = '\0',
            .endOfWord = false,
            .childNumber = 0,
            .children = NULL
    };

    readFileIn(&base);

    int ch;
    char string[400] = {0};
    char date[400] = {0};

    int field = 1;

    MOVIE *movieToAdd = NULL;

    MOVIE **list = calloc(sizeof(MOVIE *), 20);

    int selected = 0;
    int entries = 0;

    STATE state = SEARCH;
    newScreen();
    int i = 0;
    while (true)
    {
        ch = handleInput();
        if (ch == '\0') // If there was an exit command earlier, break
            break;
        //printw("%d", ch);
        switch (state) // Switches through the search, data input and journal tabs
        {
            case SEARCH:
                switch (ch) // Handle different input for the SEARCH tab
                {
                    case 9: // TAB
                        newJournal(fileName, 0);
                        state = JOURNAL;
                        break;
                    case 10: // ENTER
                        if (list[0] == NULL)
                            continue;
                        movieToAdd = list[selected];
                        for (int j = 0; j < i; j++)
                            string[j] = '\0';
                        i = 0;
                        selected = 0;
                        printInputText(" ", " ");
                        state = INPUT;
                        break;
                    default: // Characters that change display
                        if (ch == 7)
                        {
                            if (strlen(string) > 0)
                                string[--i] = '\0';
                        } else if (ch == 2) // DOWN ARROW
                            selected = (selected + 1) % 20;
                        else if (ch == 3) // UP ARROW
                            selected = (selected + 19) % 20;
                        else if (strlen(string) < 400)
                            string[i++] = (char) ch;
                        printed = 0;
                        int length;
                        trieNode *node = findPrefix(&base, string, &length);
                        getMovieList(node, 20, list);
                        newSearch(string, list, 20, selected);
                        break;
                }
                break;
            case INPUT:
                switch (ch) // Handle input for the INPUT tab
                {
                    case 10: // ENTER
                        addToUserFile(fileName, movieToAdd, string, date);
                        entries = newJournal(fileName, 1);
                        state = JOURNAL;
                        break;
                    case 74: // DELETE
                        showSearch();
                        state = SEARCH;
                        break;
                    case 9: // TAB
                        field = !field;
                        i = (int) strlen(field ? string : date);
                        break;
                    default:
                        if (ch == 7) // BACKSPACE
                        {
                            if (i > 0)
                                (field ? string : date)[--i] = '\0';
                        } else if (i < 400)
                            (field ? string : date)[i++] = (char) ch;
                        printInputText(string, date);
                        break;
                }
                break;
            case JOURNAL: // Handle input for the JOURNAL tab

                if (ch == 9) // TAB
                {
                    showSearch();
                    selected = 0;
                    state = SEARCH;
                    break;
                }
                if (entries > 0)
                {
                    if (ch == 2) // DOWN ARROW
                        selected = (selected + 1) % (entries + 1);
                    else if (ch == 3) // UP ARROW
                        selected = (selected + (entries)) % (entries + 1);
                }
                entries = newJournal(fileName, selected);
                break;
        }
    }
    endCurses();

    exit(0);
}
