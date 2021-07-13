#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
初始化
初始化成功则返回OK,否则返回ERROR
*/
Status InitList_L(LinkList *L);

/*
销毁（结构）
释放链表所占内存
*/
Status DestoryList_L(LinkList *L);

/*
置空（内容）
这里需要释放链表中非头结点处的空间
*/
Status ClearList_L(LinkList L);

/*
判空
判断链表中是否包含有效数据
返回值
TRUE：链表为空
FALSE：链表不为空
*/
Status ListEmpty_L(LinkList L);

/*
计数
返回链表包含的有效元素的数量
*/
int ListLength_L(LinkList L);

/*
当第i个元素存在时，其值赋给e并返回Ok，否则返回ERROR
*/
Status GetElem_L(LinkList L,int i,ElemType *e);

/*
查找
返回链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0
元素e是Compare函数第二个形参
*/
int LocateElem_L(LinkList L,ElemType e,Status(Compare)(ElemType,ElemType));

/*
前驱
获取cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_L(LinkList L,ElemType cur_e,ElemType *pre_e);

/*
后继
获取元素cur_e的后继
如果存在，将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_L(LinkList L,ElemType cur_e,ElemType *next_e);

/*
在带头结点的单链线性表L中第i个位置之前插入元素e
*/
Status ListInsert_L(LinkList L,int i,ElemType e);

/*
在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
*/
Status ListDelete_L(LinkList L,int i,ElemType *e);

/*
遍历
用visit函数访问链表L
*/
void ListTravese(LinkList L,void(Visit)(ElemType));

/*
头插法创建链表
*/
Status CreateListHead_L(LinkList *L,int n,char *path);

/*
尾插法创建链表
*/
Status CreateListTail_L(LinkList *L,int n,char *path);

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