#ifndef LIST_PARSER_
#define LIST_PARSER_ 1

#include <string.h>

// 代表词法单元类型
typedef enum TokenType_ {
    NAME, COMMA, LBRACK, RBRACK, T_EOF
} TokenType;

// 代表一个词法单元
typedef struct Token_ {
    TokenType type;
    char *text;
} Token;

typedef struct Input_ {
    char *text;
    // input length
    size_t len;
    // current cursor position
    int pos;
} Input;

// 获取下一个词法单元
int next_token(Input *input, Token **token);
void free_token(Token *token);
char *repr_token(const Token *token);
// 获取Token的名称
char *get_token_name(const TokenType type);

// 初始化输入字符串
int init_input(const char *input, Input **dest);
void free_input(Input *input);

void parse_list(Input *input);

#endif
