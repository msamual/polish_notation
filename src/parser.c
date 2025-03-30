#include "parser.h"

queue *parse(const char *str) {
    char *without_spaces = NULL;
    char *tokenized = NULL;
    int valid = 1;
    if ((without_spaces = remove_spaces(str)) != NULL) {
        tokenized = tokenize(without_spaces);
        if (tokenized == NULL) valid = 0;
        free(without_spaces);
    }
    queue *res = NULL;
    valid = valid && is_valid_input(tokenized);
    if (valid) res = to_postfix_notation(tokenized);
    if (tokenized != NULL) free(tokenized);
    return res;
}

int get_priority(const char *op) {
    int res = 0;
    if (strcmp(op, PLUS) == 0 || strcmp(op, MINUS) == 0) {
        res = 1;
    } else if (strcmp(op, MUL) == 0 || strcmp(op, DIV) == 0) {
        res = 2;
    } else if (strcmp(op, SIN) == 0 || strcmp(op, COS) == 0 || strcmp(op, TAN) == 0 || strcmp(op, CTG) == 0 ||
               strcmp(op, SQRT) == 0 || strcmp(op, LOG) == 0) {
        res = 4;
    } else if (strcmp(op, UNAR_MINUS) == 0) {
        res = 3;
    } else if (strcmp(op, OPEN_PAR) == 0 || strcmp(op, CLOSE_PAR) == 0) {
        res = 5;
    }
    return res;
}

void pop_while_par(stack *stack, queue *res) {
    char *tok;
    while (pop(stack, &tok)) {
        if (strcmp(tok, OPEN_PAR) == 0) {
            free(tok);
            break;
        }
        if (strcmp(tok, CLOSE_PAR) != 0) enqueue(res, tok);
        free(tok);
    }
}

void pop_while(stack *stack, queue *res, int priority) {
    char *tok;
    while (stack->size > 0 && strcmp(stack->data[stack->top], OPEN_PAR) &&
           get_priority(stack->data[stack->top]) > priority) {
        pop(stack, &tok);
        enqueue(res, tok);
        free(tok);
    }
}

void polish_process(stack *stack, queue *res, const char *token) {
    if (is_digit(*token) || strcmp(token, VAR) == 0)
        enqueue(res, token);
    else if (strcmp(token, OPEN_PAR) == 0)
        push(stack, token);
    else if (strcmp(token, CLOSE_PAR) == 0)
        pop_while_par(stack, res);
    else {
        pop_while(stack, res, get_priority(token));
        push(stack, token);
    }
}

queue *to_postfix_notation(char *str) {
    stack *stack = init();
    queue *queue = init_queue();
    if (stack != NULL && queue != NULL) {
        const char *token = strtok(str, " ");
        while (token != NULL) {
            polish_process(stack, queue, token);
            token = strtok(NULL, " ");
        }
        pop_while(stack, queue, 0);
        destroy(stack);
    }
    return queue;
}

int is_space(char c) { return c == ' ' || c == '\t' || c == '\r'; }

int is_digit(char c) { return c > 47 && c < 58; }

char *remove_spaces(const char *str) {
    int len = strlen(str);
    char *buf = calloc(len + 1, sizeof(char));
    if (buf != NULL) {
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (!is_space(str[i])) buf[j++] = str[i];
        }
    }
    return buf;
}

int add_operand(char *dst, const char *str) {
    int len = 0;
    while (*dst) dst++;
    while (*str > 47 && *str < 58) {
        *dst++ = *str++;
        len++;
    }
    return len;
}

int is_unar_minus(const char *dst) {
    int len = strlen(dst);
    return len == 0 || strchr("+-*/%^(,", dst[len - 2]) != NULL;
}

int is_hidden_star(const char *dst) {
    int len = strlen(dst);
    return len > 0 && strchr("0123456789)x", dst[len - 2]) != NULL;
}

int add_hidden_star(char *dst, const char *op) {
    if (is_hidden_star(dst)) strcat(dst, "* ");
    strcat(dst, op);
    return 1;
}

int add_token(char *dst, char *str) {
    const char *op = NULL;
    int len = 0;
    if (strstr(str, PLUS) == str)
        op = PLUS;
    else if (strstr(str, MINUS) == str)
        op = is_unar_minus(dst) ? UNAR_MINUS : MINUS;
    else if (strstr(str, MUL) == str)
        op = MUL;
    else if (strstr(str, DIV) == str)
        op = DIV;
    else if (strstr(str, OPEN_PAR) == str)
        len = add_hidden_star(dst, OPEN_PAR);
    else if (strstr(str, CLOSE_PAR) == str)
        op = CLOSE_PAR;
    else if (strstr(str, SIN) == str)
        op = SIN;
    else if (strstr(str, COS) == str)
        op = COS;
    else if (strstr(str, TAN) == str)
        op = TAN;
    else if (strstr(str, CTG) == str)
        op = CTG;
    else if (strstr(str, SQRT) == str)
        op = SQRT;
    else if (strstr(str, LOG) == str)
        op = LOG;
    else if (strstr(str, VAR) == str)
        len = add_hidden_star(dst, VAR);
    else if (is_digit(*str))
        len = add_operand(dst, str);
    else if (*str == 0)
        len = 0;
    else
        len = -1;
    if (op != NULL) {
        strcat(dst, op);
        len = strlen(op);
    }
    if (len > 0) strcat(dst, " ");
    return len;
}

char *tokenize(char *str) {
    char *res = calloc(strlen(str) * 3 + 1, sizeof(char));
    if (res != NULL) {
        int token_size;
        while (*str && (token_size = add_token(res, str)) > 0) {
            str += token_size;
        }
        if (token_size == -1) {
            free(res);
            res = NULL;
        }
    }
    return res;
}

int is_correct_brackets(char *str) {
    stack *stack = init();
    int res = 1;
    while (*str) {
        if (*str == '(')
            push(stack, OPEN_PAR);
        else if (*str == ')') {
            char *tok;
            if (pop(stack, &tok))
                free(tok);
            else
                return 0;
        }
        str++;
    }
    res = stack->size == 0;
    destroy(stack);
    return res;
}

int operands_and_operators_check(const char *str) {
    int operands_count = 0;
    int operators_count = 0;
    char *copy = strdup(str);
    const char *token = strtok(copy, " ");
    while (token != NULL) {
        if (is_digit(token[0]) || token[0] == 'x')
            operands_count++;
        else if (token[0] != '(' && token[0] != ')')
            operators_count++;
        token = strtok(NULL, " ");
    }
    free(copy);
    return operands_count > 0;
}

int is_valid_input(char *str) {
    int res = 1;
    if (strlen(str) == 0)
        res = 0;
    else if (!operands_and_operators_check(str))
        res = 0;
    else if (!is_correct_brackets(str))
        res = 0;
    return res;
}