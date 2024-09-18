#include "queue.h"

#include <stdlib.h>
#include <string.h>

// Инициализация очереди
queue *init_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    if (q) {
        q->data = NULL;  // Массив данных изначально пуст
        q->front = -1;
        q->rear = -1;
        q->size = 0;
        q->capacity = 0;
    }
    return q;
}

int enqueue(queue *q, const char *str) {
    int success = 0;  // Флаг для отслеживания успеха

    if (q != NULL) {
        // Проверяем, нужно ли увеличить ёмкость очереди
        if (q->size == q->capacity) {
            int new_capacity = (q->capacity == 0) ? 2 : q->capacity * 2;
            char **new_data = (char **)realloc(q->data, new_capacity * sizeof(char *));
            if (new_data != NULL) {
                q->data = new_data;
                q->capacity = new_capacity;
            } else {
                return 0;  // Ошибка: не удалось выделить память
            }
        }

        // Добавляем новый элемент в очередь
        if (q->front == -1) {
            q->front = 0;
        }

        q->rear = (q->rear + 1) % q->capacity;
        q->data[q->rear] = strdup(str);  // strdup выделяет память для новой строки
        q->size++;
        success = 1;  // Успешное выполнение
    }

    return success;
}

/*
int dequeue(queue *q, char **str) {
    int success = 0;  // Флаг для отслеживания успеха

    if (q != NULL && q->size > 0) {
        // Получаем строку из очереди
        *str = q->data[q->front];

        // Если в очереди один элемент, сбрасываем front и rear
        if (q->front == q->rear) {
            q->front = -1;
            q->rear = -1;
        } else {
            q->front = (q->front + 1) % q->capacity;
        }

        q->size--;
        success = 1;  // Успешное выполнение
    }

    return success;
}
*/

// Освобождение памяти
void destroy_queue(queue *q) {
    if (q) {
        for (int i = 0; i < q->size; i++) {
            int index = (q->front + i) % q->capacity;
            if (q->data[index] != NULL) {
                free(q->data[index]);  // Освобождаем каждую строку
            }
        }
        free(q->data);  // Освобождаем массив указателей
        free(q);        // Освобождаем саму структуру
    }
}
