#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "basic.h"

#define MAX_NAME_LEN 256
#define BUF_SIZE 512

char next_character(Input *input);
void consume(Input *input);
Token *NAMES(Input *input);

// 初始化Input结构体
int init_input(const char *input, Input **dest)
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
    ret_val->text = tmp_str;

    *dest = ret_val;

    return 0;
}


void free_input(Input *input)
{
    free(input->text);
    free(input);
    input = NULL;
}


int next_token(Input *input, Token **token)
{
    Token *ret_val;
    char c;

    if ((ret_val = malloc(sizeof(Token))) == NULL)
    {
        printf("next_token malloc error\n");
        return -1;
    }

    while((c = next_character(input)) != EOF && c != '\0')
    {
        switch(c)
        {
            case '\n':
            case '\t':
            case ' ':
            case '\r':
                consume(input);
                continue;
            case '[':
                consume(input);
                ret_val->type = LBRACK;
                ret_val->text = strcpy((char *) malloc(2), "[");
                *token = ret_val;
                return 0;
            case ']':
                consume(input);
                ret_val->type = RBRACK;
                ret_val->text = strcpy((char *) malloc(2), "]");
                *token = ret_val;
                return 0;
            case ',':
                consume(input);
                ret_val->type = COMMA;
                ret_val->text = strcpy((char *) malloc(2), ",");
                *token = ret_val;
                return 0;
            default:
                if (isalpha(c))
                {
                    *token = NAMES(input);
                    return 0;
                }
                else
                {
                    printf("Invalid token: %c", c);
                    exit(1);
                }
        }
    }

    ret_val->type = T_EOF;
    ret_val->text = strcpy((char *) malloc(6), "<EOF>");
    *token = ret_val;
    return 0;
}

void free_token(Token *token)
{
    free(token->text);
    free(token);
    token = NULL;
}

char *repr_token(const Token *token)
{
    char buf[BUF_SIZE];
    char *ret_val;
    char *token_name = get_token_name(token->type);

    sprintf(buf, "<%s, \"%s\">", token_name, token->text);

    if ((ret_val = (char *) malloc(strlen(buf)+1)) == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }

    strcpy(ret_val, buf);

    if (token_name)
    {
        free(token_name);
        token_name = NULL;
    }

    return ret_val;
}

char *get_token_name(const TokenType type)
{
    char buf[MAX_NAME_LEN];
    char *ret_val;

    switch(type)
    {
        case NAME:
            strcpy(buf, "NAME");
            break;
        case COMMA:
            strcpy(buf, "COMMA");
            break;
        case LBRACK:
            strcpy(buf, "LBRACK");
            break;
        case RBRACK:
            strcpy(buf, "RBRACK");
            break;
        case T_EOF:
            strcpy(buf, "EOF");
            break;
    }

    if ((ret_val = (char *) malloc(strlen(buf) + 1)) == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }
    strcpy(ret_val, buf);

    return ret_val;
}

char next_character(Input *input)
{
    return *(input->text + input->pos);
}

void consume(Input *input)
{
    input->pos++;
}

Token *NAMES(Input *input)
{
    Token *ret_val = (Token *) malloc(sizeof(Token));
    char buf[MAX_NAME_LEN];
    int index = 0;
    char c;

    while (isalpha((c = next_character(input))))
    {
        buf[index] = c;
        index++;
        consume(input);
    }

    buf[index] = '\0';
    ret_val->type = NAME;
    ret_val->text = strcpy((char *) malloc(index), buf);

    return ret_val;
}
