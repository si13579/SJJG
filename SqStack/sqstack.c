#include"sqstack.h"
/*
初始化
构造一个空栈。初始化成功则返回Ok，否则返回ERROR
*/
Status InitStack(SqStack *S){
    if (S == NULL)return ERROR;
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if ((*S).base == NULL)exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

/*
销毁（结构）
释放顺序栈所占内存
*/
Status DestoryStack(SqStack *S){
    if (S == NULL)return ERROR;
    free((*S).base);
    (*S).base = NULL;
    (*S).top = NULL;
    return OK;
}

/*
置空（内容）
只是清理顺序栈中存储的数据，不释放顺序栈所占内存
*/
Status ClearStack(SqStack *S){
    if (S == NULL || (*S).base == NULL)return ERROR;
    (*S).top = (*S).base;
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
计数
返回S的元素个数，即栈的长度
*/
int StackLength(SqStack S){
    if (S.base == NULL)return 0;
    return (int)(S.top-S.base);
}

/*
取值
若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
*/
Status GetTop(SqStack S,SElemType *e){
    if (S.base == NULL || S.top == S.base)return ERROR;
    *e = *(S.top-1);
    return OK;
}

/*
入栈
将元素e压入栈顶
*/
Status Push(SqStack *S,SElemType e){
    if (S == NULL || (*S).base == NULL)return ERROR;
    if ((*S).top - (*S).base >= (*S).stacksize){
        (*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCRMENT)*sizeof(SElemType));
        if((*S).base == NULL){
            exit(OVERFLOW);
        }
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCRMENT;
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
    *e = *(--(S->top));
    return OK;
}

/*
遍历
用visit函数访问顺序栈S
*/
Status StackTraverse(SqStack S,void(visit)(SElemType)){
    SElemType *p = S.base;
    if (S.base == NULL)return ERROR;
    while (p < top)
        visit(*p++);
    printf("\n");
    return OK;
}

/*
对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数
*/
void conversion(){
    SqStack S;
    SElemType e;
    InitStack(&S);
    int N;
    scanf("%d",&N);
    while (N){
        Push(&S,N%8);
        N /= 8;
    }
    while (!StackEmpty(S)){
        Pop(&S,&e);
        printf("%d",e);
    }
    printf("\n");
}