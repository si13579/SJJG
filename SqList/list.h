#ifndef LIST_H
#define LIST_H

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE    -1
#define OVERFLOW    -2

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10
typedef int Status;
typedef int ElemType;
typedef struct 
{
    ElemType * Elem;
    int length;
    int listsize;
}Sqlist;
//Sq sequence简称序列 
/*
构造一个空的线性表L
*/
Status InitList_Sq(Sqlist *L);

/*
初始条件：线性表L已存在
操作结果：销毁线性表L
*/
Status DestoryList_Sq(Sqlist *L);

/*
初始条件：线性表L已存在
操作结果：将L重置为空表
*/
Status ClearList_Sq(Sqlist *L);

/*
初始条件：线性表L已存在
操作结果：若L为空表，则返回True，否则返回False
*/
Status ListEmpty_Sq(Sqlist L);

/*
初始条件：线性表L已存在
操作结果：返回线性表L中元素的个数
*/
Status ListLength_Sq(Sqlist L);

/*
初始条件：线性表L已存在，i为线性表L的元素位序，1 <= i <= Listlength_Sq(L);
操作结果：用e返回L中第i个元素的值
*/
Status GetElem_Sq(Sqlist L,int i,ElemType *e);

/*
初始条件：线性表L已存在，compare()是数据元素判定函数
操作结果：返回L中第一个与e满足关系compar()的数据元素的位序。若这样的元素不存在，则返回0；
*/
Status LocateElem_Sq(Sqlist L, ElemType e,Status(compare)(ElemType,ElemType));

/*
初始条件：线性表L已存在
操作结果：若cur_e是L中的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
*/
Status PriorElem_Sq(Sqlist L,ElemType cur_e,ElemType *pre_e);

/*
初始条件：线性表L已存在
操作结果：若cur_e是L中的数据元素，且不是最后一个，则用next_e返回它的后驱，否则操作失败，next_e无定义
*/
Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType *next_e);

/*
初始条件：线性表L已存在，i为线性表L的元素位序，1 <= i <= Listlength_Sq(L)+1;
操作结果：在L中第i个位置插入新的数据元素e，L的长度加1；
*/
Status ListInSert_Sq(Sqlist *L,int i, ElemType e);

/*
初始条件：线性表L已存在且非空，i为线性表L的元素位序，1 <= i <= ListLength_Sq(L);
操作结果：删除线性表L的第i个元素，并用e返回其值，L的长度减1。
*/
Status ListDelete_Sq(Sqlist *L,int i, ElemType *e);

/*
初始条件：线性表L已存在
操作结果：依次对L的每个元素调用函数visit()。一旦visit()失败，则操作失败
*/
Status ListTraverse_Sq(Sqlist L,void(visit)(ElemType));

/*
将所有在线性表Lb但不在La中的数据元素插入到La中
*/
void Union_Sq(Sqlist *La,Sqlist Lb);

/*
已知线性表La和Lb中的元素按值非递减排列
归并La和Lb得到新的线性表Lc，Lc中的数据元素也按值非递减排列
*/
void MergeList_Sq1(Sqlist La,Sqlist Lb,Sqlist * Lc);

/*
已知线性表La和Lb中的元素按值非递减排列
归并La和Lb得到新的线性表Lc，Lc中的数据元素也按值非递减排列
*/
void MergeList_Sq2(Sqlist La,Sqlist Lb,Sqlist * Lc);
#endif