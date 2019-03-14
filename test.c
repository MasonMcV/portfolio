//
// Created by mason on 3/13/19.
//

// Inspiration from https://pdfs.semanticscholar.org/47d4/e80971ef43eebe3f63413abeefd19ec5ea2a.pdf

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>

#include "movie.h"
#include "fileio.h"

typedef struct node
{
    char *letterSequence;
    struct node **children;
    struct node **parents;
} node;

void addToTree(struct node *base, struct node *pNodes)
{

}

int main()
{
    FILE *shell;
    char *command = "wc -l ../words.txt";
    static int WORD_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &WORD_COUNT);
    pclose(shell);
    //printf("%d\n\n", WORD_COUNT);


    FILE *fp;
    char str[20] = {0};

    /* opening file for reading */
    fp = fopen("../words.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    node *nodeList[WORD_COUNT];

    int i = 0;
    while (fgets(str, 100, fp) != NULL) // read the rest of the lines
    {
        node *currentNode = (node *) malloc(sizeof(node));

        currentNode->letterSequence = (char *) malloc(sizeof(char) * strlen(str));
        strcpy(currentNode->letterSequence, str);
        nodeList[i] = currentNode;
        printf("NODE: %d, %s", (u_int) nodeList[i], nodeList[i]->letterSequence);
        i++;

    }


    for (int j = 0; j < 16; j++)
    {
        printf("%d - %s", (int) nodeList[j], nodeList[j]->letterSequence);
    }

    getchar();
    return (0);
}


/*
 * FOR WORD IN WORDS
 *  node* = find_prefix( word )             ; returns pointer to state
 *  ?? lastState = path to prefix
 *  node* firstState = the first state that has a confluence or null if none
 *  suffix = the rest of the word
 *  if firstState = null
 *      if (! has_children)
 *          node* add_suffix( word )
 *          continue;
 *      else:
 *          for each child
 *              find portion that continues after change
 *              restructure the tree
 *
 *  NOT CLEAR STARTING HERE
 *  else:
 *      Clone everything back up to the firstState
 *      go through each one and reroute parents that are not actually parents
 *
 *
 *  func replace_or_register()
 *      get the children
 *      for each child
 *          replace_or_register (child)
 *
 *
 */