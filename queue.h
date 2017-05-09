#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

/* VERSION 1.0
 *
 * node.h    - header file for AVL class
 *           - written by Ben Lindow
 *
 *    initiQueue(void);
 *      - constructor for a new Queue object
 *      - returns a malloc'd queue object
 *      - usage example: Queue* q = initQueue();
 *
 *    dequeue(Queue *);
 *      - dequeues the head of the queue
 *      - returns a pointer that was at the head of the queue
 *      - usage example: Node* n = dequeue(que);
 *
 *    enqueue(Node *, Queue *);
 *      - enqueues a node to the tail of the list
 *      - usage example: enqueue(node, que);
 *
 */

typedef struct Queue
    {
      Node* head;
      Node* tail;
      int size;
    } Queue;

extern Queue* initQueue(void);
extern Node* dequeue(Queue*);
extern void enqueue(Node*, Queue*);
#endif
