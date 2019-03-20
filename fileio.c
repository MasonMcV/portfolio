//
// Created by mason on 3/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "fileio.h"

void readFileIn(MOVIE* movieList, dafsaNode* base){

    FILE *fp;
    char str[901] = {0};

    /* opening file for reading */
    fp = fopen("../moviedata.tsv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    int i = 0;
    //fgets(str, 900, fp); // read past the first line of headers
    while (fgets(str, 900, fp) != NULL) // read the rest of the lines
    {
        //if(i > 66118)
        //    break;
        char* value = strtok(str, "\t");
        //MOVIE *movie = &movieList[i++];

        value = strtok(NULL, "\t");


        value = strtok(NULL, "\t");


        insertDAFSANode(base, value);
        //displayDAFSA(&dafsaBase, str, 0);
        /*for (int i = 0; i < dafsaBase.*//*children[0]->*//*childNumber; i++)
        {
            //printf("%d, %c\n", i, dafsaBase.children[0]->children[i]->letter);
            char str[400] = {0};
            displayDAFSA(dafsaBase.children[i], str, 0);

        }*/

    }
    printf("%d", i);
    fclose(fp);
}