//
// Created by mason on 3/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "fileio.h"

void readFileIn(MOVIE* movie_ptr){

    FILE *fp;
    char str[901] = {0};

    /* opening file for reading */
    fp = fopen("../data.tsv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }
    int i = 0;
    MOVIE* movieList = (MOVIE*)calloc(sizeof(MOVIE), 5689835);
    fgets(str, 900, fp); // read past the first line of headers
    while (fgets(str, 900, fp) != NULL) // read the rest of the lines
    {
        char* value = strtok(str, "\t\0");
        MOVIE *movie = &movieList[i++];
        movie->id = i;
        strcpy(movie->titleType, value);

        value = strtok(str, "\t\0");
        strcpy(movie->primaryTitle, value);

        value = strtok(str, "\t\0");
        strcpy(movie->originalTitle, value);

        value = strtok(str, "\t\0");
        movie->isAdult = strcmp(value, "0") ? false : true;

        value = strtok(str, "\t\0");
        movie->startYear = (int) strtol(value, NULL, 10);

        value = strtok(str, "\t\0");
        movie->endYear, (strcmp(value, "/N") == 0) ? (int) strtol(value, NULL, 10) : 0;

        value = strtok(str, "\t\0");
        movie->runtimeMinutes, (strcmp(value, "/N") == 0) ? (int) strtol(value, NULL, 10) : 0;

        value = strtok(str, "\t\0");
        strcpy(movie->genres, value);

    }
    printf("%d", i);
    fclose(fp);
}