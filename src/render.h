#ifndef RENDER_H
#define RENDER_H

// Определения размеров графика и координатных границ
#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0
#define X_MAX (4 * M_PI)
#define Y_MIN -1
#define Y_MAX 1

// Прототипы функций
void draw_graph(double (*func)(char **, int, double), char **rpn_array, int size);

#endif  // RENDER_H
