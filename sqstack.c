#include"sqstack.h"
/*
初始化
构造一个空栈，初始化成功则返回OK，否则返回ERROR
*/
Status InitStack(SqStack *S){
    if (S == NULL)return ERROR;
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S->base)exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;

    return OK;
}

/*
判空
判断顺序栈中是否包含有效数据
*/
Status StackEmpty(SqStack S){
    if (S.top == S.base)return TRUE;
    else 
        return FALSE;
}

/*
入栈
将元素e压入栈顶
*/
Status Push(SqStack *S,SElemType e){
    if (S == NULL || S->base == NULL)return ERROR;
    if (S->top - S->base >= S->stacksize){
        S->base = (SElemType *)realloc(S->base,(S->stacksize + STACKINCRMENT)*sizeof(SElemType));
        if (!S->base)exit(OVERFLOW);
    }
    *(S->top++)=e;
    return OK;
}

/*
出栈
将栈顶元素弹出，并用e接收
*/
Status Pop(SqStack *S,SElemType *e){
    if (S == NULL || S->base == NULL)return ERROR;
    if (S->top == S->base)return ERROR;
    *e = *(--S->top);
    return OK;
}
