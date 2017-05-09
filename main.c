//  Created by Benjamin Lindow on 9/15/16.
//  Copyright © 2016 Benjamin Lindow. All rights reserved.
//
//  Project2 Driver File
//
//  A program for building Binary Search Trees and AVL Balanced Trees.
//  Each tree construction supports insert, delete, report statistics,
//  and show tree functions.
//
//
//
//  Program Execution
//  -----------------
//                                                          |
//  tree [TREE TYPE] [CORPUS FILE] [INSTRUCTION FILE]       |
//                                                          |
//  [TREE TYPE] = "-a" -> AVL Tree Construction             |
//              = "-b" -> BST Tree Construction             |
//                                                          |
//  [CORUPUS FILE] = "words.txt"                            |
//                                                          |
//  [INSTRUCTION FILE] = "instructions.txt"                 |
//                                                          |
//  *********************************************************
//                                                          |
//                                                          |
//  Sample Call                                             |
//  -----------                                             |
//                                                          |
//  tree -a avltext.txt avlinstructions.txt                 |
//  tree -b bsttext.txt bstinstructions.txt                 |
//                                                          |
//  *********************************************************
//                                                          |
//  Instructions File Codes                                 |
//  -----------------------                                 |
//                                                          |
//  i = insert word                                         |
//  d = delete word                                         |
//  f = report frequency of word                            |
//  r = report statistics of tree                           |
//  s = show tree                                           |
//                                                          |
//  ---------------------------------------------------------
//
//
//
/* VERSION 1.0
 *
 * main.c    - driver file for BST/AVL
 *           - written by Ben Lindow
 *
 *    validateOptions(int, char **)
 *      - verifies correct count and type of arguments passed
 *      - usage example: validateOptions(argc, argv);
 *
 *    buildAVL(char *);
 *      - builds AVL with keys from filename
 *      - usage example: buildAVL(filename)
 *
 *    buildBST(char *);
 *      - builds BST with keys from filename
 *      - usage example: buildBST(filename);
 *
 *    runAVLInstructions(char *)
 *      - runs AVL instructions from filename
 *      - usage example: runAVLInstructions(filename)
 *
 *    runBSTInstructions(char *)
 *      - runs BST instructions from filename
 *      - usage example: runBSTInstructions(filename)
 *
 *    readStream(FILE *);
 *      - reads a token using scanner.c
 *      - returns either a string of either one word or multiple words in quotes
 *      - usage example: char* read = readStream(stdin);
 *
 *    tim(char *);
 *      - trims a char of all punction and non-alpha characters, converts uppers to lowers, collapses multiple spaces
 *      - returns a trimmed string
 *      - usage example: char* read = trim(read);
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "node.h"
#include "scanner.h"
#include "bst.h"
#include "queue.h"
#include "avl.h"

//GLOBALS
BST* b;
AVL* a;
FILE* fp;
char treeType;
char* fname1;
char* fname2;

void validateOptions(int, char **);
void buildAVL(char *);
void buildBST(char *);
void runAVLInstructions(char *);
void runBSTInstructions(char *);
char* readStream(FILE*);
void trim(char*);

int main(int argc,char **argv)
{
    validateOptions(argc, argv);
    
    if(argv[1][1] == 'b')
    {
        b = initBST();
        buildBST(fname1);
        runBSTInstructions(fname2);
    }
    else
    {
        a = initAVL();
        buildAVL(fname1);
        runAVLInstructions(fname2);
    }

    return 0;
}

void validateOptions(int argc, char **argv)
{
    //Too Many/Few Arguments
    if (argc != 4)
    {
        fprintf(stderr,"Invalid Number of Arguments\n");
        exit(1);
    }
    //Checks Dash Options
    if(argv[1][1] != 'b' && argv[1][1] != 'a')
    {
        fprintf(stderr,"Invalid Dash Option\n");
        exit(2);
    }
    //Checks First Filename
    fp = fopen(argv[2], "r");
    if (!fp)
    {
        fprintf(stderr,"Invalid File Name\n");
        exit(3);
    }
    fclose(fp);
    //Checks Second Filename
    fopen(argv[3], "r");
    if (!fp)
    {
        fprintf(stderr,"Invalid File Name\n");
        exit(4);
    }
    fclose(fp);

    treeType = argv[1][1];
    fname1 = argv[2];
    fname2 = argv[3];
}

void buildAVL(char* fname)
{
    fp = fopen(fname, "r");
    char *str = readStream(fp);
    Node* n;
    
    while(!feof(fp))
    {
        n = createNode(str);
        if(strcmp(str, "") != 0)
            insertAVL(n, a);
        str = readStream(fp);
    }
    
    fclose(fp);
}

void buildBST(char* fname)
{
    fp = fopen(fname, "r");
    char *str = readStream(fp);
    Node* n;

    while(!feof(fp))
    {
        n = createNode(str);
        if(strcmp(str, "") != 0)
            insert(n, b);
        str = readStream(fp);
    }
    
    fclose(fp);
}

void runBSTInstructions(char* fname)
{
    fp = fopen(fname, "r");
    char instruction = readChar(fp);
    Node *n;

    while(!feof(fp))
    {
        switch (instruction)
        {
            case 'i':
                n = createNode(readStream(fp));
                insert(n, b);
                break;
            case 'd':
                n = createNode(readStream(fp));
                deleet(n, b);
                break;
            case 'f':
                n = createNode(readStream(fp));
                printFreq(n, b);
                break;
            case 's':
                printTree(b);
                break;
            case 'r':
                printStats(b);
                break;
            default:
                fprintf(stderr,"Invalid Instruction\n");
                exit(4);
        }
        instruction = readChar(fp);
    }
}

void runAVLInstructions(char* fname)
{
    fp = fopen(fname, "r");
    char instruction = readChar(fp);
    Node *n;
    
    while(!feof(fp))
    {
        switch (instruction)
        {
            case 'i':
                n = createNode(readStream(fp));
                insertAVL(n, a);
                break;
            case 'd':
                n = createNode(readStream(fp));
                deleetAVL(n, a);
                break;
            case 'f':
                n = createNode(readStream(fp));
                printFreqAVL(n, a);
                break;
            case 's':
                printTreeAVL(a);
                break;
            case 'r':
                printStatsAVL(a);
                break;
            default:
                fprintf(stderr,"Invalid Instruction\n");
                exit(4);
        }
        instruction = readChar(fp);
    }
}

char * readStream(FILE *fp)
{
    char *str = NULL;
    
    if (stringPending(fp))
        str = readString(fp);
    else
        str = readToken(fp);
    
    trim(str);
    return str;
}

void trim(char* str)
{
    if (!str) { return;}
    
    char *let = str, *knew = str;
    
    while (*let)
    {
        
        if (isspace(*let))
        {
            *knew++ = *let++;
            while(isspace(*let))
                let++;
        }
        
        if (ispunct((unsigned char)*let))
            let++; //skip punc
        else if (isupper((unsigned char)*let))
        {
            *knew++ = tolower((unsigned char)*let); //make lower
            let++;
        }
        else if (isdigit((unsigned char)*let))
            let++; //skip num
        else if (let == knew) //move both increments forward
        {
            let++;
            knew++;
        }
        else
            *knew++ = *let++;
    }
    *knew = 0;
    str = knew;
    return;
}
