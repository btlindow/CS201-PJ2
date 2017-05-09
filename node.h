#ifndef NODE_H
#define NODE_H

/* VERSION 1.0
 *
 * node.h    - header file for AVL class
 *           - written by Ben Lindow
 *
 *    createNode(char *);
 *      - constructor for a new Node object
 *      - returns a malloc'd Node object initialized with a string
 *      - usage example: Node* n = createNode("string");
 *
 */

typedef struct Node
{
    char* data;
    int freq;
    int level;
    int lheight;
    int rheight;
    int height;
    
    struct Node* left;
    struct Node* right;
    struct Node* next;
    struct Node* parent;
    struct Node* fav;
} Node;

Node* createNode (char *);


#endif
