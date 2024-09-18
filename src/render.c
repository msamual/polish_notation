#include "render.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для рисования графика
void draw_graph(double (*func)(char **, int, double), char **rpn_array, int size) {
    char graph[HEIGHT][WIDTH + 1];

    // Инициализация графика
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            graph[i][j] = '.';
        }
        graph[i][WIDTH] = '\0';  // Завершаем строку нулевым символом
    }

    // Рисуем график
    for (int x = 0; x < WIDTH; x++) {
        double x_val = X_MIN + (X_MAX - X_MIN) * x / (WIDTH - 1);
        double y_val = func(rpn_array, size, x_val);  // Вычисляем значение функции для данного x

        if (isnan(y_val)) {
            printf("Ошибка при вычислении, остановка отрисовки графика.\n");
            return;  // Прерываем цикл при ошибке
        }
        // Нормализация y_val к координатам графика
        int y = (int)((y_val - Y_MIN) / (Y_MAX - Y_MIN) * (HEIGHT - 1));

        // Проверка на выход за границы
        if (y >= 0 && y < HEIGHT) {
            graph[HEIGHT - 1 - y][x] = '*';  // Инвертируем Y для правильного отображения
        }
    }

    // Вывод графика
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", graph[i]);
    }
}