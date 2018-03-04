#include <queue.h>
#include <stdio.h>
#include <stdlib.h>  // malloc
#include <string.h>  // strncpy

void init_queue(queue *q) {
  q->back = NULL;
  q->front = NULL;
  q->size = 0;
}

void enqueue(queue *q, const char *line) {
  queue_node *n = malloc(sizeof(queue_node));
  strncpy(n->line, line, MAX_LINE_LENGTH);

  if (q->front == NULL) {
    // If q is empty.
    q->front = n;
    q->back = n;
  } else {
    // Append to back.
    q->back->next = n;
    q->back = n;
  }

  q->size++;
}

void dequeue(queue *q) {
  if (q->front != NULL) {
    // If q is not empty.
    if (q->front == q->back) {
      // If q has only one node.
      free(q->front);
      q->front = NULL;
      q->back = NULL;
    } else {
      // If q has more than one node,
      // the first node gets freed,
      // and the next node becomes new front.
      queue_node *target = q->front;
      q->front = target->next;
      free(target);
    }
    q->size--;
  }
}

char *peek(queue *q) { return q->front->line; }
