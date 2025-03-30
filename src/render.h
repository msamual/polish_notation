#ifndef RENDER_H
#define RENDER_H

#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0
#define X_MAX (4 * M_PI)
#define Y_MIN -1
#define Y_MAX 1

#include "queue.h"

void draw_graph(double (*func)(queue *q, double), queue *q);

#endif
