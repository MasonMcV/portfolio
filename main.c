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


// All user input takes 400 charachters as an excessiev maximum
// All file input takes 900 as there are multiple custom fields, and therefore an excessive maximum

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

    // Set up all the variables used in the loop
    int ch;
    char search[400] = {0};
    char medium[400] = {0};
    char date[400] = {0};

    // Assign the date to today
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date, 64, "%D", tm);

    // Keep track of all the string lengths to print the cursor correctly
    int searchLength = 0;
    int mediumLength = 0;
    int dateLength = (int) strlen(date);

    // Control the input flow of the input node
    bool edit = false;
    int inputField = 0;


    // Data related to the movie list that is displayed
    MOVIE *movieToAdd = NULL;
    MOVIE **list = calloc(sizeof(MOVIE *), 20);
    int selected = 0;
    int entries = 0;

    STATE state = SEARCH;
    newScreen(); // Display the initial screen and prep all the ncurses stuff
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
                    case 9: // TAB - Go to the JOURNAL
                        newJournal(fileName, 0);
                        state = JOURNAL;
                        break;
                    case 10: // ENTER - Add the current MOVIE - INPUT
                        if (list[0] == NULL)
                            continue;
                        movieToAdd = list[selected];
                        selected = 0;
                        printInputText(medium, date, 0);
                        state = INPUT;
                        break;
                    default: // Characters that change display
                        if (ch == 7) // Backspace
                        {
                            if (strlen(search) > 0) // Go back if not already at the beginning
                                search[--searchLength] = '\0';
                        } else if (ch == 2) // DOWN ARROW
                            selected = (selected + 1) % 20; // increment
                        else if (ch == 3) // UP ARROW
                            selected = (selected + 19) % 20; // decrement
                        else if (strlen(search) < 400) // Add if not too long already
                            search[searchLength++] = (char) ch;
                        printed = 0;
                        int length;
                        trieNode *node = findPrefix(&base, search, &length);
                        getMovieList(node, 20, list);
                        newSearch(search, list, 20, selected);
                        break;
                }
                break;
            case INPUT:
                switch (ch) // Handle input for the INPUT tab
                {
                    case 10: // ENTER
                        if (edit)
                        {
                            updateRecord(fileName, selected, medium, date);
                            edit = false;
                        } else
                            addToUserFile(fileName, movieToAdd, medium, date);
                        entries = newJournal(fileName, 1);
                        state = JOURNAL;
                        break;
                    case 74: // DELETE
                        showSearch();
                        state = SEARCH;
                        break;
                    case 9: // TAB
                        inputField = !inputField;
                        printInputText(medium, date, inputField);
                        break;
                    default:
                        if (inputField == 0)
                        {
                            if (ch == 7) // BACKSPACE
                            {
                                if (mediumLength > 0)// Go back if not already at the beginning
                                    medium[--mediumLength] = '\0';
                            } else if (mediumLength < 400) // Add if not too long already
                                medium[mediumLength++] = (char) ch;

                        } else if (inputField == 1)
                        {
                            if (ch == 7) // BACKSPACE
                            {
                                if (dateLength > 0) // Go back if not already at the beginning
                                    date[--dateLength] = '\0';
                            } else if (dateLength < 400) // Add if not too long already
                                date[dateLength++] = (char) ch;
                        }
                        printInputText(medium, date, inputField);
                        break;
                }
                break;
            case JOURNAL: // Handle input for the JOURNAL tab
                if (ch == 9) // TAB
                { // Show the search and then go to it
                    showSearch();
                    selected = 0;
                    for (int j = 0; j < searchLength; j++) // Set search to all nulls
                        search[j] = '\0';
                    searchLength = 0; // Reset the search
                    state = SEARCH;
                    break;
                }
                if (ch == 74) // DELETE
                {
                    deleteRecord(fileName, selected);
                }
                if (ch == 10) // ENTER
                { // Set the edit flag to true nad let the INPUT dialog take care of it
                    edit = true;
                    printInputText(medium, date, 0);
                    for (int j = 0; j < mediumLength; j++) // Set search to all nulls
                        medium[j] = '\0';
                    mediumLength = 0;
                    for (int j = 0; j < dateLength; j++) // Set search to all nulls
                        date[j] = '\0';
                    dateLength = 0;
                    inputField = 0;
                    state = INPUT;
                    break;
                }
                if (entries > 0)
                { // Cycle through the entries
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

    freeTrie(&base);

    getchar();

    exit(0);
}
