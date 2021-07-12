#ifndef DULINKLIST_H_
#define DULINKLIST_H_

#include<stdlib.h>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBIE  -1
#define OVERFLOW    -2

typedef int Status;
typedef int ElemType;

typedef struct DuLNode{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
}DuLNode, *DuLinkList;

/*
在L中确定插入位置指针p
*/
static DuLinkList GetElemP_DuL(DuLinkList L,int i);

/*
在带头结点的双链循环线性表L中第i个位置之前插入元素e
i的合法值为1 <= i <= 表长+1
*/
Status ListInsert_DuL(DuLinkList L,int i,ElemType e);

/*
删除带头结点的双链循环线性表L的第i个元素，i的合法值为1 <= i <= 表长
*/
Status ListDelete_DuL(DuLinkList L,int i,ElemType *e);
#endif