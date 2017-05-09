#include <stdio.h>
#include <stdlib.h>

#include "node.h"

/* VERSION 1.0
 *
 * node.c    - c file for Node class
 *           - written by Ben Lindow
 *
 */


Node* createNode(char* str)
{
    Node *n = malloc(sizeof(Node));
    if (n == 0) { fprintf(stderr,"out of memory"); exit(-1); }
    
    n->freq = 1;
    n->level = 0;
    n->lheight = 0;
    n->rheight = 0;
    n->height = 1;
    n->data = str;
    n->next = NULL;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->fav = NULL;
    
    return n;
}
