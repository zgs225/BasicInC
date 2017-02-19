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

    parse_list(input);
    free_input(input);
    input = NULL;

    return 0;
}

