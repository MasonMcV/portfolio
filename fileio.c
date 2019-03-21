//
// Created by mason on 3/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "fileio.h"

void readFileIn(MOVIE** movieList, trieNode* base){

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
    //fgets(str, 900, fp); // read past the first line of headers
    while (fgets(str, 900, fp) != NULL) // read the rest of the lines
    {
        if(str[10] !='m')
            continue;

        MOVIE *movie = calloc(sizeof(MOVIE), 1);

        // Data is in the order
        // tconst	titleType	title	originalTitle	isAdult	year	endYear	runtime	genres
        strtok(str, "\t");          // tconst
        strtok(NULL, "\t");         // titleType
        char* title = strtok(NULL, "\t");         // title
        movie->title = calloc(sizeof(char), strlen(title)+1);
        strcpy(movie->title, title);
        strtok(NULL, "\t");         // originalTitle
        movie->isAdult = strcmp(strtok(NULL, "\t"), "0") ? false : true;         // isAdult
        movie->year = (int) strtol(strtok(NULL, "\t"), NULL, 10);         // year
        strtok(NULL, "\t");         // endYear
        char* minutes = strtok(NULL, "\t");
        movie->runtime = (strcmp(minutes, "/N") == 0) ? (int) strtol(minutes, NULL, 10) : 0;         // runtime
        char* genres = strtok(NULL, "\t");         // genres
        movie->genres = calloc(sizeof(char), strlen(genres)+1);
        strcpy(movie->genres, genres);

        char* value = movie->title;

        insertTrieNode(base, value, movie);
    }
    printf("%d", i);
    fclose(fp);
}