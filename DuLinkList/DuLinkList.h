#ifndef DULINKLIST_H_
#define DULINKLIST_H_

#include<stdio.h>
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

/*
初始化
初始化成功则返回OK，否则返回ERROR
*/
Status InitList_DuL(DuLinkList *L);

/*
销毁（结构）
释放双向链表所占内存
*/
Status DestoryList_DuL(DuLinkList *L);

/*
置空（内容）
这里需要释放双向链表中非头结点的空间
*/
Status ClearList_DuL(DuLinkList L);

/*
判空
判断双向链表中是否包含有有效数据
返回值
*/
Status ListEmpty_DuL(DuLinkList L);

/*
计数
返回双向循环链表中有效元素的数量
*/
int ListLength_DuL(DuLinkList L);

/*
取值
获取双向循环链表中第i个元素，将其存储到e中
如果可以找到，返回OK，否则，返回ERROR
*/
Status GetElem_DuL(DuLinkList L,int i,ElemType *e);


/*
查找
返回双向循环链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0
*/
Status LocateElem_DuL(DuLinkList L,ElemType e,Status(Compare)(ElemType,ElemType));

/*
前驱
获取元素cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_DuL(DuLinkList L,ElemType cur_e,ElemType *pre_e);

/*
后继
获取元素cur_e的后继
如果存在，则将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_DuL(DuLinkList L,ElemType cur_e,ElemType *next_e);

/*
遍历
用visit函数访问双向循环链表L
*/
void ListTraverse_DuL(DuLinkList L,void(Visit)(ElemType));

#endif