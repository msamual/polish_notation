#include <stdio.h>

#include "parser.h"
#include "polish_notation.h"
#include "queue.h"
#include "render.h"

int main() {
    char buf[100000];
    printf("Введите выражение: ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[strlen(buf) - 1] == '\n') {
        buf[strlen(buf) - 1] = '\0';
    }
    printf("buf = %s", buf);
    queue *q = parse(buf);

    char **rpn_array = copy_queue_to_array(q);
    if (rpn_array == NULL) {
        printf("Ошибка при копировании очереди\n");
        destroy_queue(q);
        return 1;
    }

    draw_graph(evaluate_polish_notation, rpn_array, q->size);

    free_array(rpn_array, q->size);
    destroy_queue(q);
    return 0;
}
