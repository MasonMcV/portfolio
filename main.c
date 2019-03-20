#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "mybool.h"
#include "movie.h"
#include "fileio.h"

int test(int test1, int *test2)
{
    for (int i = 0; i < 10; i++)
    {
        *test2 = 6;
        test1 += 50;
    }
    *test2 = 34;
    return test1;
}
int printed;

int main()
{
    // Get the number of letters / words / lines in the data.tsv file
    FILE *shell;
    char *command = "wc -l ../moviedata.tsv";
    static int WORD_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &WORD_COUNT);
    pclose(shell);
    printf("%d Letters\n\n", WORD_COUNT);

    //MOVIE *movieList = (MOVIE*)calloc(sizeof(MOVIE), WORD_COUNT);

    dafsaNode base = {
            .letter = '\0',
            .endOfWord = false,
            .childNumber = 0,
            .children = NULL
    };

    readFileIn(NULL, &base);

    char str[409];
    //displayDAFSA(&base, str, 0, -1);


    //getchar();
    //free(movieList);
    char userInput[409] = {0};
    int i = 0;
    char c;
    while (strcmp(userInput, "DONE") !=0)
    {
        //scanf("%s", userInput);
        fgets(userInput, 400, stdin);
        /*if (c== '<')
            i--;
        else
            i++;
        userInput[i] = c;*/
        int length = 0;
        printed = 0;
        dafsaNode* node = searchDAFSA(&base, userInput, &length);

        displayDAFSA(node, str, 0, 20);
        userInput[0] = '\0';
        printf("\n\nEnter Next Search: ");
    }

    exit(0);
    return 0;
}


// The longest of all of the entries - line 4670860
//tt7727908       video   Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        1       2013    \N      129     Adult,Drama