#include<stdlib.h>
#ifndef LINKLIST_H
#define LINKLIST_H

#define True    1
#define False   0
#define Ok      1
#define ERROR   0
#define INFEASIBLE      -1
#define OVERFLOW        -2
typedef int Status;
typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode * next;
}LNode,*LinkList;


/*
当第i个元素存在时，其值赋给e并返回Ok，否则返回ERROR
*/
Status GetElem_L(LinkList L,int i,ElemType *e);

/*
在带头结点的单链线性表L中第i个位置之前插入元素e
*/
Status ListInsert_L(LinkList *L,int i,ElemType e);

/*
在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
*/
Status ListDelete_L(LinkList *L,int i,ElemType *e);

/*
逆位序输入n个元素的值，建立带表头结点的单链线性表L
*/
void CreateList_L(LinkList *L,int n);

/*
已知单链线性表La和Lb的元素按值非递减排列
归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
*/
void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc);
#endif