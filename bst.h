#ifndef BST_H
#define BST_H

#include "node.h"
#include "queue.h"

/* VERSION 1.0
 *
 * bst.h    - header file for BST class
 *           - written by Ben Lindow
 *
 *    intiBST(void);
 *      - constructor for a new BST tree
 *      - returns a malloc'd tree object
 *      - usage example: BST* b = initiBST();
 *
 *    printFreq(Node *, AVL );
 *      - prints the frequency of a node in the BST tree
 *      - usage example: printFreqAVL(node, tree);
 *
 *    insert(Node *, AVL *);
 *      - inserts a new node into BST tree
 *      - usage example: insertAVL(node, tree);
 *
 *    printTree(AVL *)
 *      - show tree function that prints each node in the tree in specified formnat
 *      - usage example: printTreeAVL(tree);
 *
 *    printStats(AVL *);
 *      - prints distances to shortest null child, furthest null child, and total nodes in tree
 *      - usage example: printStatsAVL(tree);
 *
 *    deleet(Node *, AVL *);
 *      - deletes a node from an BST tree
 *      - usage example: deleetAVL(node, tree);
 *
 */


typedef struct BST
{
    Node* root;
    int height;
    int min;
    int size;
} BST;

extern BST* initBST(void);
extern void printFreq(Node *, BST *);
extern void insert(Node *, BST *);
extern void printTree(BST *);
extern void deleet(Node *, BST *);
extern void printStats(BST *);

#endif
