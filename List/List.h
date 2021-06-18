#include<stdio.h>
#include<stdlib.h>
#define True 1
#define Flase 0
#define OK 1
#define ERROR 0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int Status;
typedef int ElemType;
#define LIST_INIT_SIZE  100 //线性表存储空间的初始分配量
#define LISTINCRMENT    10  //线性表存储空间的分配增量

typedef struct 
{
    ElemType * elem;    //存储空间基址
    int length;         //当前长度
    int listsize;       //当前分配的存储容量（以sizeof(ElemType)
}Sqlist;

Status InitList_Sq(Sqlist *L);
//构造一个空的线性表L

void DestoryList_Sq(Sqlist *L);
//销毁线性表L

void ClearList_Sq(Sqlist *L);
//将线性表L重置为空表

Status ListEmptpy_Sq(Sqlist L);
//若L为空表，则返回TRUE，否则返回FALSE

Status ListLength_Sq(Sqlist L);
//返回线性表L中元素个数

Status GetElem_Sq(Sqlist L,int i,ElemType *e);
//用e返回L中第i个数据元素的值

Status LocateElem_Sq(Sqlist L,ElemType e,Status(Compare)(ElemType,ElemType));
//返回L中第一个与e满足关系compare()的数据元素的位序。
//若这样的数据元素不存在，则返回值为0.

Status PriorElem_Sq(Sqlist L,ElemType e,ElemType * pre_e);
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，
//否则操作失败，pre_e无定义。

Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType * next_e);
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，
//next_e无定义

Status ListInsert_Sq(Sqlist *L, int i, ElemType e);
//在L中第i个位置之前插入新的元素e，L的长度加1.

Status ListDelete_Sq(Sqlist *L, int i, ElemType *e);
//删除L的第i个数据元素，并用e返回其值，L的长度减1.

Status ListTraverse_Sq(Sqlist L,void(Visit)(ElemType));
//依次对L的每个数据元素调用函数visit().一旦visit()失败，则操作失败。