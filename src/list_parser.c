#include <string.h>
#include <stdlib.h>
#include "list_parser.h"


// 初始化Input结构体
int LEXER_FN(init_input)(const char *input, Input **dest)
{
    Input *ret_val;
    char *tmp_str;


    if ((ret_val = (Input *) malloc(sizeof(Input))) == NULL)
    {
        return -1;
    }

    size_t len = strlen(input);

    if ((tmp_str = (char *) malloc(len + 1)) == NULL)
    {
        return -1;
    }

    strcpy(tmp_str, input);

    ret_val->len = len;
    ret_val->pos = 0;
    ret_val->input = tmp_str;


    dest = &ret_val;

    return 0;
}


void LEXER_FN(free_input)(Input *input)
{
    free(input->input);
    free(input);
}
