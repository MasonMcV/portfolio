//
// Created by mason on 3/13/19.
//

// Inspiration from https://pdfs.semanticscholar.org/47d4/e80971ef43eebe3f63413abeefd19ec5ea2a.pdf
// Better quality and better info at http://aclweb.org/anthology/J00-1002
//
// Also look at http://www.cs.cmu.edu/afs/cs/academic/class/15451-s06/www/lectures/scrabble.pdf

/*#include <stdio.h>
#include "mybool.h"
#include <memory.h>
#include <stdlib.h>

#include "movie.h"
#include "fileio.h"


trieNode *getNewNode()
{
    trieNode *node = (trieNode *) calloc(sizeof(trieNode), 1);
    node->endOfWord = false;

    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;
    return node;
}

int getLocationForChar(char c)
{
    return c - 'a';
}

char getCharFromLocation(int i)
{
    return (char) (i + 'a');
}


void insertTrieNode(trieNode *base, char *string)
{
    trieNode *current = base;
    for (int i = 0; string[i] != '\0'; i++)
    {
        int letter = getLocationForChar(string[i]);
        if (current->children[letter] == NULL)
        {
            current->children[letter] = getNewNode();
            current->children[letter]->letter = string[i];
        }
        current = current->children[letter];
    }
    current->endOfWord = true;
}

void displayTrie(trieNode *root, char *str, int level)
{
    if (root->endOfWord)
    {
        str[level] = '\0';
        puts(str);
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            displayTrie(root->children[i], str, level + 1);
        }
    }
}*/

/*int findSubString(node *base, char *string, node *result)
{
    for (int i = 1; base->children[i] != NULL; i++)
    {
        int max = 0;
        node* maxNode = NULL;
        for (int j = 0;i<strlen(string);i++)
            if(base->children[i]->letterSequence[j] !=)
        //go through each char till a match is not found
    }

}*/

/*void addToTree(node *base, node *pNode)
{
    if (base->children[0] == NULL)
    {
        base->children[0] = pNode;
        return;
    }
    char *word;

    // printf("%d, %d, %d", sizeof(base->children[0]), 1,1);
    //if(strstr(pNode->letterSequence, ))

    //Find Prefix
}*/



/*int main()
{
    FILE *shell;
    char *command = "wc -c ../data.tsv";
    static int LETTER_COUNT = 0;
    shell = popen(command, "r");
    fscanf(shell, "%d", &LETTER_COUNT);
    pclose(shell);
    printf("%d Letters\n\n", LETTER_COUNT);


    FILE *fp;
    char str[409] = {0};

    *//* opening file for reading *//*
    fp = fopen("../data.tsv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    trieNode base = {
            .letter = '\0',
            .endOfWord = false,
            .children = NULL
    };

    int i = 0;
    while (fgets(str, 100, fp) != NULL) // read the rest of the lines
    {
        str[strlen(str) - 1] = '\0';
        insertTrieNode(&base, str);
    }
        char string[20];
    displayTrie(&base, string, 0);
    getchar();
    return (0);
}*/


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