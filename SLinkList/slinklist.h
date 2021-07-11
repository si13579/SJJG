#ifndef SLINKLIST_H
#define SLINKLIST_H
#include<stdio.h>
#include<stdlib.h>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define MAXSIZE     1000
typedef int ElemType;
typedef struct{
    ElemType    data;
    int     cur;
}component,SLinkList[MAXSIZE];

/*
在静态单链线性表L中查找第一个值为e的元素
若找到，则返回它在L中的位序，否则返回0
*/
int LocateElem_SL(SLinkList L,ElemType e);

/*
将一维数组space中各分量链成一个备用链表，sapce[0].cur为头指针
“0”表示空指针
*/
void InitSpace_SL(SLinkList *space);

/*
若备用空间链表非空，则返回分配的结点下标
*/
int Malloc_SL(SLinkList *space);

/*
将下标为k的空闲结点回收到备用链表
*/
void Free_SL(SLinkList *space,int k);

/*
依次输入集合A和B的元素，在一维数组sapce中建立表示集合(A-B)并(B-A)的静态链表，S为其头指针。
假设备用空间足够大，space[0].cur为其头指针。
*/
void difference(SLinkList *space,int *S);
#endif