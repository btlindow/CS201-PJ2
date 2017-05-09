//
//  AVL.h
//  Assign2
//
//  Created by Benjamin Lindow on 9/28/16.
//  Copyright © 2016 Benjamin Lindow. All rights reserved.
//
/* VERSION 1.0
 *
 * avl.h    - header file for AVL class
 *           - written by Ben Lindow
 *
 *    intiAVL(void);
 *      - constructor for a new AVL tree
 *      - returns a malloc'd tree object
 *      - usage example: AVL* a = initiAVL();
 *
 *    printFreqAVL(Node *, AVL );
 *      - prints the frequency of a node in the AVL tree
 *      - usage example: printFreqAVL(node, tree);
 *
 *    insertAVL(Node *, AVL *);
 *      - inserts a new node into AVL tree
 *      - usage example: insertAVL(node, tree);
 *
 *    printTreeAVL(AVL *)
 *      - show tree function that prints each node in the tree in specified formnat
 *      - usage example: printTreeAVL(tree);
 *
 *    printStats(AVL *);
 *      - prints distances to shortest null child, furthest null child, and total nodes in tree
 *      - usage example: printStatsAVL(tree);
 *
 *    deleetAVL(Node *, AVL *);
 *      - deletes a node from an AVL tree
 *      - usage example: deleetAVL(node, tree);
 *
 */

#ifndef AVL_h
#define AVL_h

#include <stdio.h>

#include "node.h"
#include "queue.h"


typedef struct AVL
{
    Node* root;
    int height;
    int min;
    int size;
} AVL;

extern AVL* initAVL(void);
extern void printFreqAVL(Node *, AVL *);
extern void insertAVL(Node *, AVL *);
extern void printTreeAVL(AVL *);
extern void printStatsAVL(AVL *);
extern void deleetAVL(Node *, AVL *);
#endif /* AVL_h */
