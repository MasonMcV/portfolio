#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "mybool.h"
#include "movie.h"
#include "fileio.h"


#include <sys/time.h>
#include <sys/resource.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
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

int main()
{
    // Get the number of letters / words / lines in the movie.tsv file
    /*FILE *shell;
    char *command = "wc -l ../moviedata.tsv";
    static int WORD_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &WORD_COUNT);
    pclose(shell);
    printf("%d Letters\n\n", WORD_COUNT);*/

    MOVIE **movieList = calloc(sizeof(MOVIE*), 1);

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
    printf("Counting took: %lf\n", endTime - startTime);

    //printf("There are %d nodes\n", countNodes(&base));

    char str[409];


    char userInput[409] = {0};

    printf("\n\nEnter Search: ");
    while (strcmp(userInput, "DONE") !=0)
    {
        fgets(userInput, 400, stdin);

        int length = 0;
        printed = 0;
        double startTime = get_time();
        trieNode* node = searchTrie(&base, userInput, &length);
        double endTime = get_time();
        displayTrie(node, str, 20);
        double finalTime = get_time();
        printf("\n\nSearch took: %lf\n", endTime - startTime);
        printf("Altogether took: %lf", finalTime - startTime);
        userInput[0] = '\0';
        printf("\n\nEnter Next Search: ");
    }

    exit(0);
}


// The longest of all of the entries - line 4670860
//tt7727908       video   Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        1       2013    \N      129     Adult,Drama