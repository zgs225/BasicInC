// Stack 数据结构和其相关方法定义
#ifndef STACK_H_
#define STACK_H_ 1

typedef struct Stack_ {
    // 当 top = -1 的时候，认为是空栈
    void **data;
    int top;
    int capacity;
} Stack;

#define isEmptyStack(S) (S->top == -1)

#endif
