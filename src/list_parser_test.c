#include "list_parser.h"
#include <stdio.h>


int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./list_parser '[a, b, [c, d]]'\n");
        return 1;
    }

    Input *input;

    if (LEXER_FN(init_input)(argv[1], &input) < 0) {
        printf("Input init error\n");
        return 1;
    }

    printf("Input: %s, length: %zu, current position: %d\n", input->input, input->len, input->pos);

    LEXER_FN(free_input)(input);

    return 0;
}

