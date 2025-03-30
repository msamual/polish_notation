#ifndef STACK_H
#define STACK_H

typedef struct {
    char **data;
    int top;
    int size;
    int capacity;
} stack;

stack *init();
int push(stack *s, const char *str);
int pop(stack *s, char **str);
void destroy(stack *s);

#endif
