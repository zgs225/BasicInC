#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "basic.h"

#define MAX_NAME_LEN 256
#define BUF_SIZE 512
#define K_LOOKAHEADS 2

char next_character(Input *input);
void consume(Input *input);
Token *NAMES(Input *input);

void match(TokenType type, Input *input);
void parse_list_internal(Input *input);
void match_elements(Input *input);
void match_element(Input *input);
void consume_token(Input *input);
TokenType LA(int i);
void LT(int i, Token **token);

Token *lookaheads[K_LOOKAHEADS] = {0};
int current_pos = 0;

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
            case '=':
                consume(input);
                ret_val->type = EQUALS;
                ret_val->text = strcpy((char *) malloc(2), "=");
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
        case EQUALS:
            strcpy(buf, "EQUALS");
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

void parse_list(Input *input)
{
    for (int i = 0; i < K_LOOKAHEADS; i++)
    {
        consume_token(input);
    }
    parse_list_internal(input);
}

void parse_list_internal(Input *input)
{
    match(LBRACK, input);
    match_elements(input);
    match(RBRACK, input);
}

void match_elements(Input *input)
{
    match_element(input);
    Token *lookahead;
    LT(1, &lookahead);
    while (lookahead->type == COMMA)
    {
        match(COMMA, input);
        match_elements(input);
    }
}

void match_element(Input *input)
{
    if (LA(1) == NAME && LA(2) == EQUALS)
    {
        match(NAME, input);
        match(EQUALS, input);
        match(NAME, input);
    }
    else if (LA(1) == NAME)
    {
        match(NAME, input);
    }
    else if (LA(1) == LBRACK)
    {
        parse_list_internal(input);
    }
    else
    {
        Token *lookahead;
        LT(1, &lookahead);
        printf("excepting name or list; found %s", repr_token(lookahead));
        exit(1);
    }
}

void match(TokenType type, Input *input)
{
    Token *lookahead;
    LT(1, &lookahead);

    if (type == lookahead->type)
    {
        consume_token(input);
    }
    else
    {
        printf("Error: expect \"%s\", but actual is \"%s\"\n", get_token_name(type), lookahead->text);
        exit(1);
    }
}

void consume_token(Input *input)
{
    Token *tmp;
    if (next_token(input, &tmp) < 0)
    {
        printf("next token error\n");
        exit(1);
    }

    if (lookaheads[current_pos])
    {
        free_token(lookaheads[current_pos]);
    }

    lookaheads[current_pos] = tmp;
    current_pos = (current_pos + 1) % K_LOOKAHEADS;
}

TokenType LA(int i)
{
    Token *tmp;
    LT(i, &tmp);
    return tmp->type;
}

void LT(int i, Token **token)
{
    Token *tmp = lookaheads[(current_pos + i - 1) % K_LOOKAHEADS];
    *token = tmp;
}
