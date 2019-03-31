//
// Created by mason on 3/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "fileio.h"

/* * Reads in the movie File from the IMDB Database
   * and loads it into the trie
   * Uses strtok to parse each line
   * Exits if no file found
   */
void readFileIn(trieNode *base)
{

    FILE *fp;
    char str[901] = {0};

    // opening file for reading
    fp = fopen("../data.tsv", "r");
    if (fp == NULL)
    {
        perror("Error opening data file");
        exit(1);
    }

    int i = 0;
    while (fgets(str, 900, fp) != NULL) // read the lines of the file and add them to the trie
    {
        strtok(str, "\t");          // tconst
        if (strcmp(strtok(NULL, "\t"), "movie") != 0)         // titleType
        {
            continue;
        }


        MOVIE *movie = calloc(sizeof(MOVIE), 1);

        // Data is in the order
        // tconst	titleType	title	originalTitle	isAdult	year	endYear	runtime	genres
        char *title = strtok(NULL, "\t");         // title
        movie->title = calloc(sizeof(char), strlen(title) + 1);
        strcpy(movie->title, title);
        strtok(NULL, "\t");         // originalTitle
        movie->isAdult = strcmp(strtok(NULL, "\t"), "0") ? false : true;         // isAdult
        movie->year = (int) strtol(strtok(NULL, "\t"), NULL, 10);         // year
        strtok(NULL, "\t");         // endYear
        char *minutes = strtok(NULL, "\t");
        movie->runtime = (strcmp(minutes, "/N") == 0) ? (int) strtol(minutes, NULL, 10) : 0;         // runtime
        char *genres = strtok(NULL, "\t");         // genres
        movie->genres = calloc(sizeof(char), strlen(genres) + 1);
        strcpy(movie->genres, genres);
        movie->genres[strlen(movie->genres) - 1] = '\0';

        char *value = movie->title;

        insertTrieNode(base, value, movie);
        i++;
    }
    fclose(fp);
}

// Add the specified movie to the specified file
void addToUserFile(char *name, MOVIE *movie, char *medium, char *date)
{
    FILE *fp;
    fp = fopen(name, "a"); // For appending
    if (fp == NULL)
    {
        printf("SOMETHING WENT WRONG OPENING USER FILE");
        exit(0);
    }
    if (date[0] == '\0')
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(date, 64, "%D", tm);
    }
    fprintf(fp, "%s \t%d \t%d \t%s \t%s \t%s \n",
            movie->title, movie->year, movie->runtime, movie->genres, medium, date);
    fclose(fp);
}

// Gets the lines from the file and calls the specified callback function on it
int getFileWords(char *name, void (*callback)(char *, int))
{
    FILE *fp;
    fp = fopen(name, "r"); // open for reading
    if (fp == NULL)
    {
        (*callback)("No data yet, Try adding a movie", 1);
        return 0;
    }
    int i = 0;
    char str[900];
    while (fgets(str, 900, fp) != NULL) // read the rest of the lines
    {
        (*callback)(str, i++);
    }
    fclose(fp);
    return i - 1;
}

// Go through the file till the record number matches,
// Dont add that one to the array
// Print the array to the file;
void deleteRecord(char *name, int number)
{


    FILE *fp;
    fp = fopen(name, "r"); // For appending
    if (fp == NULL)
    {
        printf("SOMETHING WENT WRONG OPENING USER FILE");
        exit(0);
    }
    char recordList[900][900];
    char str[900];
    int i = 0;
    int j = 0;
    while (fgets(str, 900, fp) != NULL) // read the lines of the file and add them to the array
    {
        if (i != number)
        {
            strcpy(recordList[j], str);
            j++;
        }
        i++;
    }
    fp = fopen(name, "w");
    if (fp == NULL)
    {
        printf("SOMETHING WENT WRONG OPENING USER FILE");
        exit(0);
    }
    for (int k = 0; k < j; k++)
    {
        fprintf(fp, "%s", recordList[k]);
    }

    fclose(fp);
}

// Go through the file till the record number matches,
// Add the updated text to that one
// Print the array to the file;
void updateRecord(char *name, int number, char *medium, char *date)
{
    FILE *fp;
    fp = fopen(name, "r"); // For appending
    if (fp == NULL)
    {
        printf("SOMETHING WENT WRONG OPENING USER FILE");
        exit(0);
    }
    char recordList[900][900];
    char str[900];
    int i = 0;
    while (fgets(str, 900, fp) != NULL) // read the lines of the file and add them to the array
    {
        if (i != number)
        {
            strcpy(recordList[i], str);
        } else
        {
            strcpy(recordList[i], strtok(str, "\t")); // title
            strcat(recordList[i], "\t");
            strcat(recordList[i], strtok(NULL, "\t")); // year
            strcat(recordList[i], "\t");
            strcat(recordList[i], strtok(NULL, "\t")); // runtime minutes
            strcat(recordList[i], "\t");
            strcat(recordList[i], strtok(NULL, "\t")); // genres
            strcat(recordList[i], "\t");
            strcat(recordList[i], medium);
            strcat(recordList[i], "\t");
            strcat(recordList[i], date);
            strcat(recordList[i], "\n");
        }
        i++;
    }
    fp = fopen(name, "w");
    if (fp == NULL)
    {
        printf("SOMETHING WENT WRONG OPENING USER FILE");
        exit(0);
    }
    for (int k = 0; k < i; k++)
    {
        fprintf(fp, "%s", recordList[k]);
    }

    fclose(fp);
}
