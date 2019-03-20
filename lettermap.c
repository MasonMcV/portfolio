//
// Created by mason on 3/16/19.
//

#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "lettermap.h"

/*void getMapping(char *string, int *mapping)
{
    //int *mapping = (int *) calloc(sizeof(int), strlen(string));
    for (int i = 0; string[i] != '\0'; i++)
    {
        char c = string[i];
        if (isalpha(c))
        {
            mapping[i] = toupper(c) - (char) 65;
        } else
        {
            if (c >= (char) 32 && c <= 64)
            {
                mapping[i] = c - (char) 5;
            } else
            {
                mapping[i] = (char) 58;
            }
        }


        //mapping[i] = c;
    }
    //return mapping;
}*/

void getMapping(char *string, int *mapping)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        char c = string[i];
        if (isalpha(c))
        {
            mapping[i] = toupper(c) - (char) 65;
        } else if (isalnum(c))
        {
            mapping[i] = c - (char) 22;
        } else
        {
            mapping[i] = 48;
        }
    }
}

/*char *getStringFromMapping(int *mapping)
{
    int length = sizeof(mapping) / sizeof(mapping[0]);

    char *string = (char *) calloc(sizeof(char), length);

    for (int i = 0; i < length; i++)
    {
        char c = (char) mapping[i];
        if (c < 26)
        {
            string[i] = c + (char) 65;
        } else
        {
            string[i] = c + (char) 5;
        }
    }
    return string;
}*/

char getCharFromMapping(int mapping)
{
    if (mapping < 26)
        return (char)(mapping + 65);
    if (mapping >= 26 && mapping < 36)
        return (char)(mapping + 22);
    return '?';
}
