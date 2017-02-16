#include <stdio.h>
#include "basic.h"


int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./list_parser '[a, b, [c, d]]'\n");
        return 1;
    }

    Input *input;

    if (init_input(argv[1], &input) < 0)
    {
        printf("Input init error\n");
        return 1;
    }

    printf("Input: %s, length: %zu, current position: %d\n", input->text, input->len, input->pos);

    free_input(input);

    return 0;
}

