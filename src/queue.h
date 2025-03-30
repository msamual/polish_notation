#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int front;
    int rear;
    int size;
    int capacity;
} queue;

queue *init_queue();
int enqueue(queue *q, const char *str);
int dequeue(queue *q, char **str);
void destroy_queue(queue *q);

#endif
