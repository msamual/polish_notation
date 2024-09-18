#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>  // Для определения типа size_t

// Структура очереди для хранения строк
typedef struct {
    char **data;   // Массив для хранения строк
    int front;     // Индекс переднего элемента
    int rear;      // Индекс заднего элемента
    int size;      // Текущий размер очереди
    int capacity;  // Текущая вместимость очереди
} queue;

// Функции для работы с очередью
queue *init_queue();                     // Инициализация очереди
int enqueue(queue *q, const char *str);  // Добавление строки в очередь
int dequeue(queue *q, char **str);       // Удаление строки из очереди
void destroy_queue(queue *q);            // Освобождение памяти

#endif  // QUEUE_H
