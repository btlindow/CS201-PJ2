#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/* VERSION 1.0
 *
 * bst.c     - c file for BST class
 *           - written by Ben Lindow
 *
 *    removeNode(Node *);
 *      - removes Node for BST
 *      - usage example: removeNode(n);
 
 *    countChilds(Node *);
 *      - counts the number of children a node has
 *      - returns in of the number of nodes
 *      - usage example: int count = countChilds(node);
 
 *    removeOnly(Node *)
 *      - removes a leaf from a tree
 *      - usage example: removeOnly(leaf);
 
 *    removeSingle(Node *)
 *      - removes a node that has one child
 *      - usage example: removeSingle(node);
 
 *    removeDouble(Node *)
 *      - removes a node that has two children
 *      - usage example: removeDouble(node);
 
 *    newSingleRoot(Node *);
 *      - modified tree root if it is trying to be deleted with one child
 *      - usage example: newSingleRoot(root);
 
 *    newSingleRoot(Node *);
 *      - modified tree root if it is trying to be deleted with two children
 *      - usage example: newDoubleRoot(root);
 
 *    climb(Node *, AVL *);
 *      - generic function to climb a tree
 *      - returns value equal to a Node*, the Node* before where an inserted Node
 *      - should  be, or NULL if a Node is not found
 *      - usage example: Node* n = climb(node,tree);
 
 *    put(Node *, Node *, AVL *);
 *      - inserts a Node to the left or write a specific Node in a tree
 *      - usage example: put(node,parent,tree);
 
 *    leftOrRightAVL(Node *);
 *      - determines if a node is a left or right child
 *      - returns char L if a left child, else char R
 *      - usage example: char LorR = leftOrRightAVL(node)
 
      isLeaf(Node *);
 *      - determines if a node is a leaf or not
 *      - returns 1 if node is a leaf, else 0
 *      - usage example: int x = isLeafAVL(node);
 
 *    isEmptyTree(AVL *);
 *      - determines if Tree is Empty
 *      - returns 0 if tree is empty, else 1.
 *      - usage example: int x = isEmptyTree(tree);

 *    getStats(AVL *);
 *      - uses tree traversal to gather information and store in tree
 *      - usage example: getStats(tree);
 
 *    printNode(Node *);
 *      - prints node information in a specific format
 *      - usage example: printNode(node);
 
 
 *    findSuc(Node *);
 *      - generic function to find successor of a node
 *      - returns pointer to a successor, else NULL
 *      - usage example: Node* s = findSuc(node);
 
 */

static Node* climb(Node *, BST *);
static void put(Node *, Node *, BST *);
static char leftOrRight(Node *);
static int isLeaf(Node *);
static void removeNode(Node *, BST *);
static int countChilds(Node *);
static void removeOnly(Node *, BST *);
static void removeSingle(Node *, BST* b);
static Node* findSuc(Node *);
static void newSingleRoot(Node *, BST* b);
static void newDoubleRoot(Node *, BST* b);
static void removeDouble(Node* n, BST* b);
static int isEmptyTree(BST *);
static void getStats(BST *);
static void printNode(Node *);


BST* initBST(void)
{
    BST* b = malloc(sizeof(BST));
    if (b == 0) { fprintf(stderr,"out of memory"); exit(-1); }

    b->size = 0;
    b->height = 0;
    b->min = -1;
    b->root = NULL;
    return b;
}

void insert(Node* n, BST* b)
{
    if (!b->root)
    {
        b->root = n;
        n->parent = n;
        b->size++;
        return;
    }
    else
        put(n, climb(n, b), b);
}

void printTree(BST* b)
{
    if(isEmptyTree(b)) {return;}

    Queue* q = initQueue();
    Node* n;
    int level = -1;
    
    enqueue(b->root, q);
    b->root->level = 0;
    
    
    while(q->size > 0)
    {
        n = dequeue(q);
        
        if(n->level != level)
        {
            if(level != -1)
                printf("\n");
            printf("%d: ", ++level);
        }
        
        printNode(n);
        
        if(n->left)
        {
            enqueue(n->left, q);
            n->left->level = n->level + 1;
        }
        
        if(n->right)
        {
            enqueue(n->right, q);
            n->right->level = n->level + 1;
        }
    }
}

void printStats(BST* b)
{
    if(isEmptyTree(b)) {return;}
    getStats(b);
    printf("\nNumber of Nodes in BST: %d\n", b->size);
    printf("Distance to Closest Null Child: %d\n", b->min);
    printf("Distance to Furthest Null Child: %d\n", b->height);
}

void printFreq(Node* n, BST* b)
{
    if (isEmptyTree(b)) {return;}
    Node* ptr = climb(n, b);

    if(strcmp(n->data, ptr->data) == 0)
        printf("\"%s\" has frequency %d\n", ptr->data, ptr->freq);
    else
        printf("The string \"%s\" does not exist.\n", n->data);
        
}

void deleet(Node* ptr, BST* b)
{
    if(isEmptyTree(b)) {return;}

    Node* n = climb(ptr, b);
    if(strcmp(n->data, ptr->data) != 0) { printf("The string \"%s\" does not exist.\n", ptr->data); return; }

    n->freq--;

    if(!n->freq)
    {
        removeNode(n, b);
        b->size--;
    }
}

static void printNode(Node* n)
{
    if(isLeaf(n))
        printf("=");
    printf("%s(%s)%d%c ", n->data, n->parent->data, n->freq, leftOrRight(n));
}

static void getStats(BST* b)
{
    isEmptyTree(b);
    
    Queue* q = initQueue();
    Queue* lq = initQueue();
    Node* n;
    
    enqueue(b->root, q);
    b->root->level = 0;
    
    while(q->size > 0)
    {
        n = dequeue(q);
        
        if(!n->left || !n->right)
            enqueue(n, lq);
        
        if(n->left)
            enqueue(n->left, q);
        
        if(n->right)
            enqueue(n->right, q);
    
    }
    b->min = lq->head->level;
    b->height = lq->tail->level;
}


static Node* climb(Node* n, BST* b)
{
    Node* ptr = b->root;

    while(ptr)
    {
        if(strcmp(n->data, ptr->data) < 0 && ptr->left)
            ptr = ptr->left;
        else if(strcmp(n->data, ptr->data) > 0 && ptr->right)
            ptr = ptr->right;
        else
            break;
    }
    return ptr;
}

static void put(Node* n, Node* t, BST* b)
{   //If Equal, Update Freq and Return
    if(strcmp(n->data, t->data) == 0)
    {
        t->freq++;
        return;
    }
    //Add Left
    if(strcmp(n->data, t->data) < 0)
        t->left = n;
    //Add Right
    else if(strcmp(n->data, t->data) > 0)
        t->right = n;

    n->parent = t;
    b->size++;
}

static void removeNode(Node* n, BST* b)
{
    int num = countChilds(n);

    switch (num)
    {
        case 0:
            removeOnly(n, b);
            break;
        case 1:
            removeSingle(n, b);
            break;
        case 2:
            removeDouble(n, b);
            break;
        default:
            break;
    }
    return;
}

static void removeOnly(Node* ptr, BST* b)
{
    if (ptr == b->root)
    {
        b->root = NULL;
        return;
    }

    Node* n = ptr->parent;

    if(n->right == ptr)
        n->right = NULL;
    else
        n->left = NULL;
    //ptr->parent = NULL;
}

static void removeSingle(Node* ptr, BST* b)
{
    Node* n;

    if(ptr->left)
        n = ptr->left;
    else
        n = ptr->right;

    if (b->root == ptr)
    {
        newSingleRoot(n, b);
        return;
    }

    Node* p = ptr->parent;
    if(p->right == ptr)
        p->right = n;
    else
        p->left = n;

    n->parent = p;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->parent = NULL;
}

static void removeDouble(Node* ptr, BST* b)
{
    Node* n = findSuc(ptr);

    if(n == ptr->right)
    {
        if(ptr == b->root)
        {
            n->left = ptr->left;
            n->left->parent = n;
            n->parent = n;
            b->root = n;
            return;
        }

        n->parent = ptr->parent;
        n->left = ptr->left;
        n->left->parent = n;
    }
    else
    {
        Node* p = n->parent;
        if(n->right)
        {
            p->left = n->right;
            n->right->parent = p;
        }
        else
            p->left = NULL;

        if (ptr != b->root)
            {
                n->parent = ptr->parent;
                n->left = ptr->left;
                ptr->left->parent = n;
                n->right = ptr->right;
                n->right->parent = n;
            }
        else
        {
            newDoubleRoot(n, b);
            return;
        }
    }

    Node* p = ptr->parent;
    if (p->left == ptr)
        p->left = n;
    else
        p->right = n;

    if(ptr == b->root)
    {
        newDoubleRoot(n, b);
        return;
    }

    ptr->left = NULL;
    ptr->right = NULL;
    ptr->parent = NULL;
}

static int countChilds(Node *n)
{
    if (!n->left && !n->right) {return 0;}
    else if (n->right && n->left) {return 2;}
    else return 1;
}

static Node* findSuc(Node* n)
{
    Node* ptr = n->right;
    while(ptr->left)
        ptr = ptr->left;
    return ptr;
}

static char leftOrRight(Node* n)
{
    Node* p = n->parent;
    if (n == p)
        return 'X';
    else if (p->left && strcmp(p->left->data, n->data) == 0)
        return 'L';
    else
        return 'R';
}

static int isLeaf(Node* n)
{
    if (!n->left && !n->right)
        return 1;
    else
        return 0;
}

static void newSingleRoot(Node* n, BST* b)
{
    b->root = n;
    n->parent = n;
}

static void newDoubleRoot(Node* n, BST* b)
{
    n->left = b->root->left;
    n->left->parent = n;
    n->right = b->root->right;
    n->right->parent = n;
    b->root = n;
    n->parent = n;
}

static int isEmptyTree(BST* b)
{
    if(!b->root)
    {
        printf("Empty Tree!\n");
        return 1;
    }
    else
        return 0;
}
