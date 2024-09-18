#include "stack.h"

#include <stdlib.h>
#include <string.h>

// Инициализация стека
stack *init() {
    stack *s = (stack *)malloc(sizeof(stack));
    if (s) {
        s->data = NULL;  // Массив данных изначально пуст
        s->top = -1;
        s->size = 0;
        s->capacity = 0;
    }
    return s;
}

int push(stack *s, const char *str) {
    int success = 0;  // Флаг для отслеживания успеха

    if (s != NULL) {
        if (s->top + 1 == s->capacity) {
            int new_capacity = (s->capacity == 0) ? 2 : s->capacity * 2;
            char **new_data = (char **)realloc(s->data, new_capacity * sizeof(char *));
            if (new_data != NULL) {
                s->data = new_data;
                s->capacity = new_capacity;
            } else {
                success = 0;  // Ошибка: не удалось выделить память
            }
        }

        if (s->top + 1 != s->capacity) {
            s->data[s->top + 1] = strdup(str);  // Копируем строку
            s->top++;
            s->size++;
            success = 1;  // Успешное выполнение
        }
    }

    return success;
}

int pop(stack *s, char **str) {
    int success = 0;  // Флаг для отслеживания успеха

    if (s != NULL && s->top != -1) {
        *str = s->data[s->top];  // Передаем строку наружу
        s->top--;
        s->size--;
        success = 1;  // Успешное выполнение
    }

    return success;
}

// Освобождение памяти
void destroy(stack *s) {
    if (s) {
        for (int i = 0; i <= s->top; i++) {
            free(s->data[i]);  // Освобождаем каждую строку
        }
        free(s->data);
        free(s);
    }
}
