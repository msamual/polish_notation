#include "queue.h"

queue *init_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    if (q) {
        q->data = NULL;
        q->front = -1;
        q->rear = -1;
        q->size = 0;
        q->capacity = 0;
    }
    return q;
}

int enqueue(queue *q, const char *str) {
    int success = 0;

    if (q != NULL) {
        if (q->size == q->capacity) {
            int new_capacity = (q->capacity == 0) ? 2 : q->capacity * 2;
            char **new_data = (char **)realloc(q->data, new_capacity * sizeof(char *));
            if (new_data != NULL) {
                q->data = new_data;
                q->capacity = new_capacity;
            } else {
                return 0;
            }
        }

        if (q->front == -1) {
            q->front = 0;
        }

        q->rear = (q->rear + 1) % q->capacity;
        q->data[q->rear] = strdup(str);
        q->size++;
        success = 1;
    }

    return success;
}

int dequeue(queue *q, char **str) {
    int success = 0;

    if (q != NULL && q->size > 0) {
        *str = q->data[q->front];

        if (q->front == q->rear) {
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front + 1) % q->capacity;
        }

        q->size--;
        success = 1;
    }

    return success;
}

void destroy_queue(queue *q) {
    if (q) {
        for (int i = 0; i < q->size; i++) {
            int index = (q->front + i) % q->capacity;
            if (q->data[index] != NULL) {
                free(q->data[index]);
            }
        }
        free(q->data);
        free(q);
    }
}
