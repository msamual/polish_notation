#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define PLUS "+"
#define MINUS "-"
#define UNAR_MINUS "~"
#define MUL "*"
#define DIV "/"
#define OPEN_PAR "("
#define CLOSE_PAR ")"
#define SIN "sin"
#define COS "cos"
#define TAN "tan"
#define CTG "ctg"
#define SQRT "sqrt"
#define LOG "ln"
#define VAR "x"

queue *parse(const char *str);
int get_priority(const char *op);
void pop_while_par(stack *stack, queue *res);
void pop_while(stack *stack, queue *res, int priority);
void polish_process(stack *stack, queue *res, const char *token);
queue *to_postfix_notation(char *str);
int is_space(char c);
int is_digit(char c);
int add_operand(char *dst, const char *str);
int is_unar_minus(const char *dst);
int add_token(char *dst, char *str);
char *tokenize(char *str);
int is_correct_brackets(char *str);
int operands_and_operators_check(const char *str);
int is_valid_input(char *str);
char *remove_spaces(const char *str);

#endif