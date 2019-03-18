//
// Created by mason on 3/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "fileio.h"

void readFileIn(MOVIE* movieList, trieNode* base){

    FILE *fp;
    char str[901] = {0};

    /* opening file for reading */
    fp = fopen("../otherdata.tsv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }
    dafsaNode dafsaBase = {
            .letter = '\0',
            .endOfWord = false,
            .childNumber = 0,
            .children = NULL
    };

    int i = 0;
    movieList = (MOVIE*)calloc(sizeof(MOVIE), 5689835);
    fgets(str, 900, fp); // read past the first line of headers
    while (fgets(str, 900, fp) != NULL) // read the rest of the lines
    {
        char* value = strtok(str, "\t");
        MOVIE *movie = &movieList[i++];
        movie->id = i;

        //strcpy(movie->tconst, value);

        value = strtok(NULL, "\t");
        //strcpy(movie->titleType, value);


        value = strtok(NULL, "\t");
        //strcpy(movie->primaryTitle, value);

        //insertTrieNode(base, value);
        insertDAFSANode(&dafsaBase, value);
        //displayDAFSA(&dafsaBase, str, 0);
        /*for (int i = 0; i < dafsaBase.*//*children[0]->*//*childNumber; i++)
        {
            //printf("%d, %c\n", i, dafsaBase.children[0]->children[i]->letter);
            char str[400] = {0};
            displayDAFSA(dafsaBase.children[i], str, 0);

        }*/
        //printf("\n");
        //value = strtok(NULL, "\t");
        //strcpy(movie->originalTitle, value);

        //value = strtok(NULL, "\t");
        //movie->isAdult = strcmp(value, "0") ? false : true;

        //value = strtok(NULL, "\t");
        //movie->startYear = (int) strtol(value, NULL, 10);

        //value = strtok(NULL, "\t");
        //movie->endYear, (strcmp(value, "/N") == 0) ? (int) strtol(value, NULL, 10) : 0;

        //value = strtok(NULL, "\t");
        //movie->runtimeMinutes, (strcmp(value, "/N") == 0) ? (int) strtol(value, NULL, 10) : 0;

        //value = strtok(NULL, "\t");
        //strcpy(movie->genres, value);

    }
    printf("%d", i);
    fclose(fp);
}