#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include <math.h>

#include "queue.h"
#include "stack.h"

#define BUFFER_SIZE 50

#define EPSILON 1e-9

int is_number(const char *str);
int is_unary_operator(const char *operator);
int is_binary_operator(const char *operator);
int perform_unary_operation(stack *s, const char *operator);
int perform_binary_operation(stack *s, const char *operator);
int perform_operation(stack *s, const char *operator);

double evaluate_polish_notation(queue *q, double x_value);

double handle_negation(double operand);
double handle_sin(double operand);
double handle_cos(double operand);
double handle_tan(double operand);
double handle_ctg(double operand);
double handle_sqrt(double operand);
double handle_ln(double operand);

#endif
