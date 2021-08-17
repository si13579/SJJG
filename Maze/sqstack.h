#ifndef SQSTACK_H
#define SQSTACK_H

#include<stdio.h>
#include<stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2

#define STACK_INIT_SIZE 100     //顺序栈存储空间的初始分配量
#define STACKINCRMENT   10      //顺序栈存储空间的分配增量

typedef int Status;

//迷宫通道块的坐标
typedef struct {
    int x;
    int y;
} PosType; //通道块的横纵坐标定义

//通道块信息
typedef struct {
    int ord;    //通道块的序号
    PosType seat; //通道块的坐标位置
    int di;     //下一个应当访问的方向
} SElemType;

typedef struct {
    SElemType *base;    //栈底指针
    SElemType *top;     //栈顶指针
    int stacksize;      //当前已分配的存储空间
}SqStack;

/*
初始化
构造一个空栈，初始化成功则返回OK，否则返回ERROR
*/
Status InitStack(SqStack *S);

/*
判空
判断顺序栈中是否包含有效数据
*/
Status StackEmpty(SqStack S);

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

#endif