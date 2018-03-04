#ifndef QUEUE_H
#define QUEUE_H
#define MAX_LINE_LENGTH 1024

typedef struct queue_node {
  struct queue_node *next;
  char line[MAX_LINE_LENGTH];
} queue_node;

typedef struct queue {
  queue_node *front;
  queue_node *back;
  int size;
} queue;

void init_queue(queue *q);
void enqueue(queue *q, const char *line);
void dequeue(queue *q);
char *peek(queue *q);
#endif
