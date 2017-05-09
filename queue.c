#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* VERSION 1.0
 *
 * queue.c   - c file for Queue class
 *           - written by Ben Lindow
 *
 */

Queue* initQueue(void)
{
  Queue *q = malloc(sizeof(Queue));
  if (q == 0) { fprintf(stderr,"out of memory"); exit(-1); }
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

void enqueue(Node* n, Queue* q)
{
  if(!q->head)
  {
    q->head = n;
    q->tail = n;
  }
  else
  {
    q->tail->next = n;
    q->tail = n;
  }
  q->size++;
}

Node* dequeue(Queue* q)
{
  if (!q->head)
    return NULL;
  else
  {
    Node* ptr = q->head;
    q->head = q->head->next;
    ptr->next = NULL;
    q->size--;
    return ptr;
  }
}
