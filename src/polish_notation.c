#include "polish_notation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_number(const char *str) {
    char *endptr;
    strtod(str, &endptr);
    return *endptr == '\0';
}

int is_unary_operator(const char *operator) {
    int found = 0;  // Флаг для отслеживания нахождения оператора
    const char *unary_operators[] = {"~", "sin", "cos", "tan", "ctg", "sqrt", "ln"};
    int num_unary_operators = sizeof(unary_operators) / sizeof(unary_operators[0]);

    for (int i = 0; i < num_unary_operators; i++) {
        if (strcmp(operator, unary_operators[i]) == 0) {
            found = 1;
            break;
        }
    }
    return found;
}

int is_binary_operator(const char *operator) {
    int found = 0;  // Флаг для отслеживания нахождения оператора
    const char *binary_operators[] = {"+", "-", "*", "/"};
    int num_binary_operators = sizeof(binary_operators) / sizeof(binary_operators[0]);

    for (int i = 0; i < num_binary_operators; i++) {
        if (strcmp(operator, binary_operators[i]) == 0) {
            found = 1;
            break;
        }
    }
    return found;
}

double handle_negation(double operand) { return -operand; }

double handle_sin(double operand) { return sin(operand); }

double handle_cos(double operand) { return cos(operand); }

double handle_tan(double operand) {
    double result = 0;
    if (fabs(fmod(operand, M_PI) - M_PI_2) > EPSILON) {
        result = tan(operand);  // Тангенс определен
    }
    return result;
}

double handle_ctg(double operand) {
    double result = 0;
    if (fabs(fmod(operand, M_PI)) > EPSILON) {
        result = 1 / tan(operand);  // Котангенс определен
    }
    return result;
}

double handle_sqrt(double operand) {
    double result = 0;
    if (operand >= 0) {
        result = sqrt(operand);  // Корень определен
    }
    return result;
}

double handle_ln(double operand) {
    double result = 0;
    if (operand > 0) {
        result = log(operand);  // Логарифм определен
    }
    return result;
}

int perform_unary_operation(stack *s, const char *operator) {
    int success = 1;  // Флаг успешности выполнения

    if (s->top < 0) {
        success = 0;
        printf("Ошибка: не хватает операндов для выполнения операции\n");
    } else {
        char *operand_str;
        pop(s, &operand_str);
        double operand = strtod(operand_str, NULL);
        free(operand_str);  // Освобождаем строку после извлечения

        double result = 0;
        if (strcmp(operator, "~") == 0) {
            result = handle_negation(operand);
        } else if (strcmp(operator, "sin") == 0) {
            result = handle_sin(operand);
        } else if (strcmp(operator, "cos") == 0) {
            result = handle_cos(operand);
        } else if (strcmp(operator, "tan") == 0) {
            result = handle_tan(operand);
        } else if (strcmp(operator, "ctg") == 0) {
            result = handle_ctg(operand);
        } else if (strcmp(operator, "sqrt") == 0) {
            result = handle_sqrt(operand);
        } else if (strcmp(operator, "ln") == 0) {
            result = handle_ln(operand);
        }

        char *result_str = (char *)malloc(BUFFER_SIZE * sizeof(char));
        snprintf(result_str, BUFFER_SIZE, "%f", result);
        push(s, result_str);  // Строка помещена в стек, её нужно будет освободить позже
        free(result_str);
    }

    return success;
}

int perform_binary_operation(stack *s, const char *operator) {
    int success = 1;

    if (s->size < 2) {
        success = 0;
        printf("n/a Некорректный стек для бинарной операции (не хватает операндов)\n");
    } else {
        char *operand2_str;
        pop(s, &operand2_str);
        double operand2 = strtod(operand2_str, NULL);
        free(operand2_str);

        char *operand1_str;
        pop(s, &operand1_str);
        double operand1 = strtod(operand1_str, NULL);
        free(operand1_str);

        double result = 0;
        if (strcmp(operator, "+") == 0) {
            result = operand1 + operand2;
        } else if (strcmp(operator, "-") == 0) {
            result = operand1 - operand2;
        } else if (strcmp(operator, "*") == 0) {
            result = operand1 * operand2;
        } else if (strcmp(operator, "/") == 0) {
            if (operand2 == 0) {
                result = 0;
            } else {
                result = operand1 / operand2;
            }
        }

        char *result_str = (char *)malloc(BUFFER_SIZE * sizeof(char));
        snprintf(result_str, BUFFER_SIZE, "%f", result);
        push(s, result_str);  // Строка помещена в стек, её нужно будет освободить позже
        free(result_str);
    }

    return success;
}

int perform_operation(stack *s, const char *operator) {
    int success = 0;

    if (is_unary_operator(operator)) {
        success = perform_unary_operation(s, operator);
    } else if (is_binary_operator(operator)) {
        success = perform_binary_operation(s, operator);
    }

    return success;
}

double evaluate_polish_notation(char **array, int size, double x_value) {
    stack *s = init();
    double result = NAN;
    int success = 1;

    for (int i = 0; i < size; i++) {
        const char *token = array[i];

        if (strcmp(token, "x") == 0) {
            char *x_str = (char *)malloc(BUFFER_SIZE * sizeof(char));
            if (!x_str) {
                success = 0;
                break;
            }
            snprintf(x_str, BUFFER_SIZE, "%f", x_value);
            push(s, x_str);
            free(x_str);
        } else if (is_number(token)) {
            push(s, token);
        } else {
            if (!perform_operation(s, token)) {
                success = 0;
                break;
            }
        }
    }

    if (success && s->size == 1) {
        char *result_str;
        pop(s, &result_str);
        result = strtod(result_str, NULL);
        free(result_str);  // Освобождаем строку результата
    } else {
        printf("n/a (ошибка: неправильное количество элементов в стеке)\n");
    }

    destroy(s);  // Убедитесь, что destroy освобождает все строки в стеке
    return result;
}

char **copy_queue_to_array(const queue *q) {
    if (q == NULL || q->size == 0) {
        return NULL;  // Если очередь пуста, возвращаем NULL
    }

    // Выделяем память под массив строк
    char **array = (char **)malloc(q->size * sizeof(char *));
    if (array == NULL) {
        return NULL;  // Ошибка выделения памяти
    }

    // Копируем строки из очереди в массив
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        array[i] = strdup(q->data[index]);  // Копируем строку
    }

    return array;
}

void free_array(char **array, int size) {
    if (array) {
        for (int i = 0; i < size; i++) {
            free(array[i]);  // Освобождаем каждую строку
        }
        free(array);  // Освобождаем сам массив
    }
}