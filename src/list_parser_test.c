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
    Token *token;

    if (init_input(argv[1], &input) < 0)
    {
        printf("Input init error\n");
        return 1;
    }

    while(1)
    {
        if (next_token(input, &token) < 0)
        {
            printf("next_token error\n");
            return 1;
        }
        printf("%s\n", repr_token(token));

        if (token->type == T_EOF)
            break;

        free_token(token);
        token = NULL;
    }

    if (token)
    {
        free_token(token);
        token = NULL;
    }

    free_input(input);
    input = NULL;

    return 0;
}

