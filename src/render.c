#include "render.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void draw_graph(double (*func)(queue *, double), queue *q) {
    char graph[HEIGHT][WIDTH + 1];
    int size = q->size;
    int rear = q->rear;
    int front = q->front;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            graph[i][j] = '.';
        }
        graph[i][WIDTH] = '\0';
    }

    for (int x = 0; x < WIDTH; x++) {
        double x_val = X_MIN + (X_MAX - X_MIN) * x / (WIDTH - 1);
        double y_val = func(q, x_val);
        q->size = size;
        q->front = front;
        q->rear = rear;

        if (isnan(y_val)) {
            printf("Error: Invalid value\n");
            return;
        }
        int y = (int)((y_val - Y_MIN) / (Y_MAX - Y_MIN) * (HEIGHT - 1));

        if (y >= 0 && y < HEIGHT) {
            graph[HEIGHT - 1 - y][x] = '*';
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", graph[i]);
    }
}