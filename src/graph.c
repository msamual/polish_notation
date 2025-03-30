#include <stdio.h>

#include "parser.h"
#include "polish_notation.h"
#include "queue.h"
#include "render.h"

int main() {
    char buf[100000];
    printf("Input expression: ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n') {
        buf[strlen(buf) - 1] = '\0';
    }
    queue *q = parse(buf);
    if (q == NULL) {
        printf("Error: incorrect input\n");
        destroy_queue(q);
        return 1;
    }

    draw_graph(evaluate_polish_notation, q);

    destroy_queue(q);
    return 0;
}
