//  Created by Benjamin Lindow on 9/28/16.
//  Copyright © 2016 Benjamin Lindow. All rights reserved.
//

/* VERSION 1.0
 *
 * avl.c     - c file for AVL Class
 *           - written by Ben Lindow
 *
 *    climbAVL(Node *, AVL *);
 *      - generic function to climb an AVL tree
 *      - returns value equal to a Node*, the Node* before where an inserted Node
 *      - should  be, or NULL if a Node is not found
 *      - usage example: Node* n = climb(node,tree);
 
 *    putAVL(Node *, Node *, AVL *);
 *      - inserts a Node to the left or write a specific Node in an AVL tree
 *      - usage example: put(node,parent,tree);
 
 *    leftOrRightAVL(Node *);
 *      - determines if a node is a left or right child
 *      - returns char L if a left child, else char R
 *      - usage example: char LorR = leftOrRightAVL(node)
 
      isLeafAVL(Node *);
 *      - determines if a node is a leaf or not
 *      - returns 1 if node is a leaf, else 0
 *      - usage example: int x = isLeafAVL(node);
 
 *    isEmptyTreeAVL(AVL *);
 *      - determines if AVL Tree is Empty
 *      - returns 0 if tree is empty, else 1.
 *      - usage example: int x = isEmptyTreeAVL(tree);

 *    setBalance(Node *);
 *      - sets the balance of a node in an AVL tree
 *      - usage example: setBalance(node);

 *    max(int, int);
 *      - generic max function
 *      - returns max of two ints
 *      - usage example: int x = max(a,b);

 *    sibling(Node *);
 *      - finds the sibling of a node
 *      - returns pointer to sibling if exists, else returns NULL
 *      - usage example: Node* sib = sibling(node);

 *    setFavorite(Node *);
 *      - sets the favorite node of a node to it's favorite child
 *      - usage example: setFavorite(node);

 *    isLinear(Node *);
 *      - determines if parent, n, and favorite are in a linear fashion
 *      - returns 0 if not, else returns 1
 *      - usage example: int x = isLinear(node);

 *    rotateRight(Node *);
 *      - rotates a node right UP the tree
 *      - usage example: rotateRight(node);

 *    rotateLeft(Node *);
 *      - rotates a node left UP the tree
 *      - usage example: rotateLeft(node);
 
 *    fixup(Node *, AVL *);
 *      - fixup function starting at a specific node for post-insertion into AVL tree
 *      - usage example: fixus(node, tree);

 *    linearRotate(Node *, AVL *);
 *      - performs linear rotation on parent, node, and favorite
 *      - usage example: linearRotate(n);

 *    nonlinearRotate(Node *, AVL *);
 *      - performs nonlinear rotation about parent, node, and favorite
 *      - usage example: nonlinearRotate(node, tree);

 *    heavy(Node *);
 *      - determines if a node is left heavy or right heavy
 *      - returns - if a node is left heavy, + if right, NULL if balanced
 *      - usage example: char heav = heavy(node);

 *    getStats(AVL *);
 *      - uses tree traversal to gather information and store in tree
 *      - usage example: getStats(tree);

 *    printNode(Node *);
 *      - prints node information in a specific format
 *      - usage example: printNode(node);
 
 *    swapNodes(Node *, Node *);
 *      - swaps the data betwwen two nodes
 *      - usage example: swapNodes(p, q);
 
 *    findSuc(Node *);
 *      - generic function to find successor of a node
 *      - returns pointer to a successor, else NULL
 *      - usage example: Node* s = findSuc(node);
 
 *    findPred(Node *);
 *      - generic function to find predecessor of a node
 *      - returns pointer to a predecessor, else NULL
 *      - usage example: Node* s = findPred(node);
 
 *    deleteFixup(Node *, AVL *);
 *      - fixup function starting at a specific node for post-deletion from an AVL tree
 *      - usage example: deleteFixup(node, tree);
 
 *    doSwap(Node *);
 *      - determines which two nodes to swap prior to deletion and performs swap if possible
 *      - returns pointer to lower of two nodes, else returns original node
 *      - usage example: Node* del = doSwap(n, p);
 
 *    trimLeaf(Node *);
 *      - generic prune function to remove leaf from tree
 *      - usage example: trimLeaf(n);
 */

#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* climbAVL(Node *, AVL *);
static void putAVL(Node *, Node *, AVL *);
static char leftOrRightAVL(Node *);
static int isLeafAVL(Node *);
static int isEmptyTreeAVL(AVL *);
static void setBalance(Node *);
static int max(int, int);
static Node* sibling(Node *);
static void setFavorite(Node *);
static int isLinear(Node *);
static void rotateRight(Node *);
static void rotateLeft(Node *);
static void fixup(Node *, AVL *);
static void linearRotate(Node *, AVL *);
static void nonlinearRotate(Node *, AVL *);
static char* heavy(Node *);
static void getStats(AVL *);
static void printNode(Node *);
static void swapNodes(Node *, Node *);
static Node* findSuc(Node *);
static Node* findPred(Node *);
static void deleteFixup(Node *, AVL *);
static Node* doSwap(Node *);
static void trimLeaf(Node *);

AVL* initAVL(void)
{
    AVL* a = malloc(sizeof(AVL));
    if (a == 0) { fprintf(stderr,"out of memory"); exit(-1); }
    
    a->size = 0;
    a->height = 0;
    a->min = -1;
    a->root = NULL;
    return a;
}

void insertAVL(Node* n, AVL* a)
{
    if (!a->root)
    {
        a->root = n;
        n->parent = n;
        a->size++;
    }
    else
        putAVL(n, climbAVL(n, a), a);
}

void deleetAVL(Node* ptr, AVL* b)
{
    if(isEmptyTreeAVL(b)) {return;}
    
    Node* n = climbAVL(ptr, b);
    if(strcmp(n->data, ptr->data) != 0) { printf("The string \"%s\" does not exist.\n", ptr->data); return;}
 
    n->freq--;
    
    if(!n->freq)
    {
        if(n == b->root && isLeafAVL(b->root))
        {
            b->root = NULL;
            b->size = 0;
            return;
        }
        
        
        Node* s = doSwap(n);
        deleteFixup(s, b);
        trimLeaf(s);
        b->size--;
    }
}

void printTreeAVL(AVL* b)
{
    if(isEmptyTreeAVL(b)) {return;}
    
    Queue* q = initQueue();
    Node* n;
    int level = -1;
    
    enqueue(b->root, q);
    b->root->level = 0;
    
    while(q->size > 0)
    {
        n = dequeue(q);
        n->next = NULL;
        
        if(n->level != level)
        {
            if(level != -1)
                printf("\n");
            printf("%d:", ++level);
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

void printStatsAVL(AVL* b)
{
    if(isEmptyTreeAVL(b)) {return;}
    
    getStats(b);
    printf("\nNumber of Nodes in AVL: %d\n", b->size);
    printf("Distance to Closest Null Child: %d\n", b->min);
    printf("Distance to Furthest Null Child: %d\n", b->height);
}

void printFreqAVL(Node* n, AVL* b)
{
    if(isEmptyTreeAVL(b)) {return;}
    Node* ptr = climbAVL(n, b);
    
    if(strcmp(n->data, ptr->data) == 0)
        printf("\"%s\" has frequency %d\n", ptr->data, ptr->freq);
    else
    {
        printf("The string \"%s\" does not exist.\n", n->data);
        return;
    }
}

static void deleteFixup(Node* n, AVL* a)
{
    Node* p;
    n->height = 0;
    while(n != a->root)
    {
        p = n->parent;
        
        if(p->fav == n)
        {
            setBalance(p);
            n = n->parent;
        }
        
        else if(!p->fav)
        {
            setBalance(p);
            return;
        }
        
        else
        {
            Node* s = sibling(n);
            Node* f = s->fav;
            
            if(f && !isLinear(s))
            {
                nonlinearRotate(s, a);
                setBalance(p);
                setBalance(s);
                setBalance(f);
                n = f;
            }
            
            else
            {
                linearRotate(s, a);
                setBalance(p);
                setBalance(s);
                if(!f)
                    return;
                else
                    n = f;
            }
        }
    }
}


static Node* doSwap(Node* n)
{
    if (isLeafAVL(n)) return n;
    
    Node* swap;
    
    if(n->left)
        swap = findPred(n);
    else
        swap = findSuc(n);
    
    swapNodes(n, swap);
    
    return swap;
    
}


static void swapNodes(Node* n, Node* q)
{
    char* t_data = n->data;
    int t_freq = n->freq;
    
    n->data = q->data;
    n->freq = q->freq;
    
    q->data = t_data;
    q->freq = t_freq;
}

static Node* climbAVL(Node* n, AVL* b)
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

static void putAVL(Node* n, Node* t, AVL* b)
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
    fixup(n, b);
}

static void fixup(Node* n, AVL* a)
{
    Node* p;
    while(n != a->root)
    {
        p = n->parent;
        
        if(sibling(n) && p->fav == sibling(n))
        {
            setBalance(p);
            return;
        }
        else if(p->fav == NULL)
        {
            setBalance(p);
            n = n->parent;
        }
        else
        {
            Node* f = n->fav;
            
            if(f && !isLinear(n))
            {
                nonlinearRotate(n, a);
                setBalance(n);
                setBalance(p);
                setBalance(f);
                setBalance(f->parent); //deviation
            }
            else
            {
                linearRotate(n, a);
                setBalance(p);
                setBalance(n);
                setBalance(n->parent); //deviation
            }
            return;
        }
    }
}

static void nonlinearRotate(Node* n, AVL* a)
{
    Node* p = n->parent;
    Node* f = n->fav;
    int pflag = 0;
    
    if(p == a->root)
    {
        pflag = 1;
        Node* temp = createNode("TEMPROOT");
        p->parent = temp;
        temp->left = p;
        a->root = temp;
    }
    
    if(p->right == n && n->left == f)
    {
        rotateRight(f);
        rotateLeft(f);
    }
    else
    {
        rotateLeft(f);
        rotateRight(f);
    }
    
    if(pflag)
    {
        a->root = f;
        f->parent = f;
    }
}

static void linearRotate(Node* n, AVL* a)
{
    int type = isLinear(n);
    Node* p = n->parent;
    int pflag = 0;
    
    if(p == a->root)
    {
        pflag = 1;
        Node* temp = createNode("TEMPROOT");
        p->parent = temp;
        temp->left = p;
        a->root = temp;
    }
    
    if(type == 1)
        rotateLeft(n);
    else
        rotateRight(n);
    
    if(pflag)
    {
        a->root = n;
        n->parent = n;
    }
    
}

static char leftOrRightAVL(Node* n)
{
    Node* p = n->parent;
    if (n == p)
        return 'X';
    else if (p->left && strcmp(p->left->data, n->data) == 0)
        return 'L';
    else
        return 'R';
}

static int isLeafAVL(Node* n)
{
    if (!n->left && !n->right)
        return 1;
    else
        return 0;
}


static void setBalance(Node* n)
{
    if(n->left)
        n->lheight = n->left->height;
    else
        n->lheight = 0;
    
    if (n->right)
        n->rheight = n->right->height;
    else
        n->rheight = 0;
    
    n->height = max(n->lheight, n->rheight) + 1;
    setFavorite(n);
}

static Node* sibling(Node* n)
{
    Node* p = n->parent;
    if(p->right == n)
        return p->left;
    else
        return p->right;
}

static void setFavorite(Node* n)
{
    if (n->left && n->right)
    {
        if (n->left->height == n->right->height)
            n->fav = NULL;
        else if (n->left->height > n->right->height)
            n->fav = n->left;
        else
            n->fav = n->right;
    }
    else if(!n->left && !n->right)
        n->fav = NULL;
    else if (n->left && !n->right)
        n->fav = n->left;
    else
        n->fav = n->right;
}

static int isLinear(Node *n)
{
    Node* p = n->parent;
    Node* f = n->fav;
    
    if(p->right == n && n->right == f)
        return 1;
    else if (p->left == n && n->left == f)
        return 2;
    else
        return 0;
}

static void rotateRight(Node* n)
{
    Node* p = n->parent;
    
    //set grandparent
    if(p->parent->left == p)
        p->parent->left = n;
    else
        p->parent->right = n;
    n->parent = p->parent;
    
    //set parent's left to n's right
    p->left = n->right;
    if (p->left)
        p->left->parent = p;
    
    //set parent to n->right
    n->right = p;
    p->parent = n;
}

static void rotateLeft(Node* n)
{
    Node* p = n->parent;
    
    //set grandparent
    if(p->parent->left == p)
        p->parent->left = n;
    else
        p->parent->right = n;
    n->parent = p->parent;
    
    //set parent's left to n's right
    p->right = n->left;
    if (p->right)
        p->right->parent = p;
    
    //set parent to n->right
    n->left = p;
    p->parent = n;
}

static void getStats(AVL* b)
{
    isEmptyTreeAVL(b);
    
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
    b->min = lq->head->level;
    b->height = lq->tail->level;
}

static char* heavy(Node* n)
{
    if(!n->fav) return NULL;
    if(n->fav == n->left) return "-";
    else return "+";
}

static int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

static Node* findSuc(Node* n)
{
    Node* ptr = n->right;
    while(ptr->left)
        ptr = ptr->left;
    return ptr;
}

static Node* findPred(Node* n)
{
    Node* ptr = n->left;
    while(ptr->right)
        ptr = ptr->right;
    return ptr;
}

static void trimLeaf(Node* n)
{
    Node* p = n->parent;
    Node* c;
    
    if(n->left)
        c = n->left;
    else
        c = n->right;
    
    if(c)
        c->parent = p;
    
    if(p->left == n)
        p->left = c;
    else
        p->right = c;
    
    setBalance(p);
}

static void printNode(Node* n)
{
    printf(" ");
    if(isLeafAVL(n))
        printf("=");
    printf("%s", n->data);
    if(heavy(n))
        printf("%s", heavy(n));
    printf("(%s", n->parent->data);
    if(heavy(n->parent))
        printf("%s", heavy(n->parent));
    printf(")%d", n->freq);
    printf("%c", leftOrRightAVL(n));
}

static int isEmptyTreeAVL(AVL* b)
{
    if(!b->root)
    {
        printf("Empty Tree!\n");
        return 1;
    }
    else
        return 0;
}
