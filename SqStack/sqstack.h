#ifndef SQSTACK_H_
#define SQSTACK_H_

#include<stdio.h>
#include<stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2    

#define STACK_INIT_SIZE 100
#define STACKINCRMENT   10    

typedef int Status;
typedef int SElemType;
typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

/*
初始化
构造一个空栈。初始化成功则返回Ok，否则返回ERROR
*/
Status InitStack(SqStack *S);

/*
销毁（结构）
释放顺序栈所占内存
*/
Status DestoryStack(SqStack *S);

/*
置空（内容）
只是清理顺序栈中存储的数据，不释放顺序栈所占内存
*/
Status ClearStack(SqStack *S);

/*
判空
判断顺序栈中是否包含有效数据
*/
Status StackEmpty(SqStack S);

/*
计数
返回S的元素个数，即栈的长度
*/
int StackLength(SqStack S);

/*
取值
若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
*/
Status GetTop(SqStack S,SElemType *e);

/*
入栈
将元素e压入栈顶
*/
Status Push(SqStack *S,SElemType e);

/*
出栈
将栈顶元素弹出，并用e接收
*/
Status Pop(SqStack *S,SElemType *e);

/*
遍历
用visit函数访问顺序栈S
*/
Status StackTraverse(SqStack S,void(visit)(SElemType));

/*
对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数
*/
void conversion();

#endif