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
typedef int Status;
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
void InitSpace_SL(SLinkList space);

/*
若备用空间链表非空，则返回分配的结点下标
*/
int Malloc_SL(SLinkList space);

/*
将下标为k的空闲结点回收到备用链表
*/
void Free_SL(SLinkList space,int k);

/*
依次输入集合A和B的元素，在一维数组sapce中建立表示集合(A-B)并(B-A)的静态链表，S为其头指针。
假设备用空间足够大，space[0].cur为其头指针。
*/
void difference(SLinkList space,int *S);

//静态链表操作
/*
初始化
先初始化备用空间，而后从备用空间中申请头结点的空间，进而完成链表的初始化
初始化成功则使用S存储头结点索引，且返回OK，否则返回ERROR
*/
Status InistList_SL(SLinkList space,int *S);

/*
销毁（结构）
释放静态链表所占内存，即将静态链表所有结点空间移入备用空间列表中。
*/
Status DestoryList_SL(SLinkList space,int *S);

/*
置空（内容）
这里需要释放静态链表中非头结点处的空间
*/
Status ClearList_SL(SLinkList space,int S);

/*
判空
判断静态链表中是否包含有效数据
返回值
TRUE：  静态链表为空
FALSE： 静态链表不为空
*/
Status ListEmpty_SL(SLinkList space,int S);

/*
计数
返回静态链表包含的有效元素的数量
*/
int ListLength_SL(SLinkList space,int S);

/*
取值
获取静态链表中第i个元素，将其存储到e中
如果可以找到，返回OK，否则，返回ERROR
*/
Status GetElem_SL(SLinkList space, int S,int i, ElemType * e);

/*
查找
返回静态链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0.
*/
int LocateElem(SLinkList space,int S,ElemType e,Status(Compare)(ElemType,ElemType));

/*
前驱
获取元素cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_SL(SLinkList space, int S,ElemType cur_e,ElemType *pre_e);

/*
后继
获取元素cur_e的后继
如果存在，将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_SL(SLinkList space,int S, ElemType cur_e,ElemType *next_e);

/*
插入
向静态链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR
*/
Status ListInsert_SL(SLinkList space, int S,int i,ElemType e);

/*
删除
删除静态链表第i个位置上的元素，并将被删元素存储到e中
删除成功则返回OK，否则返回ERROR
*/
Status ListDelete_SL(SLinkList space, int S,int i,ElemType *e);

/*
遍历
用visit函数访问静态链表
*/
void ListTraverse_SL(SLinkList space,int S,void(Visit)(ElemType));

// 以图形化形式输出结构
void PrintList_SL(SLinkList space,int S);

static void Visit(ElemType e);

#endif