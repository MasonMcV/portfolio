#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#include "movie.h"
#include "fileio.h"

int main()
{
    MOVIE* movieList = NULL;
    readFileIn(movieList);
    getchar();

    free(movieList);
    return (0);
}


// The longest of all of the entries - line 4670860
//tt7727908       video   Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        Yufukuna kurashi kara gokuhin seikatsu e kyu tenraku! Chichi no kaisha ga tosan shite shakkin * sen man-en! Byojakuna haha wa netakiri... 18-sai moto ojosama ga ototo no gakuhi o kasegu tame, shiritsu no meimon koko o chutai shite kesshinokakugode AV shutsuen! Hatsu go kkun 5 renpatsu! Nodo oku irama-hatsu 18 shurui no omocha de iki gomon! Denma jigoku shisshin kuritorisu bishonure sukusui hatsu shiofuki!        1       2013    \N      129     Adult,Drama