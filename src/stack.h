#ifndef STACK_H
#define STACK_H

// Переопределение структуры стека для хранения строк
typedef struct {
    char **data;   // Массив для хранения строк
    int top;       // Индекс верхушки стека
    int size;      // Текущий размер массива
    int capacity;  // Текущая вместимость стека
} stack;

// Функции для работы со стеком
stack *init();                        // Инициализация стека
int push(stack *s, const char *str);  // Добавление строки в стек
int pop(stack *s, char **str);        // Удаление строки из стека
void destroy(stack *s);               // Освобождение памяти

#endif  // STACK_H
