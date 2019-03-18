#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#include "movie.h"
#include "fileio.h"

int test(int test1, int *test2)
{
    for (int i=0;i<10;i++)
    {
        *test2 = 6;
        test1 += 50;
    }
    *test2 = 34;
    return test1;
}

int main()
{
    int a = 0, b = 1;
    printf("%d, %d\n", a, b);
    a = test(a, &b);
    printf("%d, %d\n", a, b);
    printf("%d \n\n", (int) sizeof(dafsaNode*));
    // Get the number of letters / words / lines in the data.tsv file
    FILE *shell;
    char *command = "wc -l ../lessdata.tsv";
    static int LETTER_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &LETTER_COUNT);
    pclose(shell);
    printf("%d Letters\n\n", LETTER_COUNT);

    MOVIE *movieList = NULL;

    trieNode base = {
            .letter = '\0',
            .endOfWord = false,
            .children = NULL
    };

    readFileIn(movieList, &base);


    getchar();
    free(movieList);
    return (0);
}


// The longest of all of the entries - line 4670860
//tt7727908       video   Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        1       2013    \N      129     Adult,Drama