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
    DISPLAY
} STATE;

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
    printf("Building took: %lf\n", endTime - startTime);

    startTime = get_time();
    int nodes = countNodes(&base);
    endTime = get_time();
    printf("Counting took: %lf, There are %d nodes\n", endTime - startTime, nodes);


    int ch;
    char string[400] = {0};


    STATE state = SEARCH;
    newScreen();
    int i = 0;
    while (true)
    {
        ch = handleInput();
        if (ch == '\0') // If there was an exit command earlier, break
            break;
        switch (state)
        {
            case SEARCH:
                if (ch == 9) // TAB
                {
                    state = DISPLAY;
                    break;
                }
                if (ch == 7) // 7 = BACKSPACE
                {
                    if (strlen(string) > 0)
                        string[--i] = '\0';
                } else if (ch == 10) // 10 = ENTER
                {
                    for (int j = 0; j < i; j++)
                        string[j] = '\0';
                    i = 0;
                    state = INPUT;
                    break;
                } else
                {
                    if (strlen(string) < 400)
                        string[i++] = (char) ch;
                }

                int length;
                printed = 0;
                trieNode *node = findPrefix(&base, string, &length);
                MOVIE **list = calloc(sizeof(MOVIE *), 20);
                getMovieList(node, 20, list);
                newSearch(string, list, 20);
                break;
            case INPUT:
                if (ch == 10) // ENTER
                {
                    state = DISPLAY;
                    break;
                }
                if (ch == 9) // TAB
                {
                    state = SEARCH;
                    break;
                }
                break;
            case DISPLAY:
                if (ch == 9) // TAB
                {
                    state = SEARCH;
                    break;
                }
                break;
        }
    }
    endCurses();

    exit(0);
}
