#include"List.h"

Status InitList_Sq(Sqlist *L){
    //构造一个新的线性表L
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (L->elem) exit(OVERFLOW); //存储分配失败
    L->length = 0;                //空表长度为0
    L->listsize = LIST_INIT_SIZE; //初始存储容量
    return OK;   
}

void DestoryList_Sq(Sqlist *L){
//销毁线性表L
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
}

void ClearList_Sq(Sqlist *L){
//将线性表L重置为空表
    L->length = 0;
}

Status ListEmptpy_Sq(Sqlist L){
//若L为空表，则返回TRUE，否则返回FALSE
    return L.length == 0 ? True : Flase;
}
Status ListLength_Sq(Sqlist L){
//返回线性表L中元素个数
    return L.length;
}

Status GetElem_Sq(Sqlist L,int i,ElemType *e){
//用e返回L中第i个数据元素的值
    if (i < 1 || i > L.length)
        return ERROR;
    else
        *e = L.elem[i-1];
    return OK;
}
Status LocateElem_Sq(Sqlist L,ElemType e,Status(Compare)(ElemType,ElemType)){
//返回L中第一个与e满足关系compare()的数据元素的位序。
//若这样的数据元素不存在，则返回值为0.
    int i = 1;
    ElemType * p = L.elem;
    while (i <= L.length && !Compare(*p++,e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

Status PriorElem_Sq(Sqlist L,ElemType cur_e,ElemType * pre_e){
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，
//否则操作失败，pre_e无定义。
    int i = 1;
    if (L.elem[0] != cur_e){
        while (i < L.length && L.elem[i] != cur_e)
            i++;
        if (i < L.length){
            *pre_e = L.elem[i-1];
            return OK;
        }
    }
    return ERROR;
}

Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType * next_e){
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，
//next_e无定义
    int i = L.length-1;
    if (L.elem[i] != cur_e){
        while (i > 0 && L.elem[i] != cur_e)
            i--;
        if (i > 0){
            *next_e = L.elem[i+1];
            return OK;
        }
    }
    return ERROR;
}

Status ListInsert_Sq(Sqlist *L, int i, ElemType e){
//在L中第i个位置之前插入新的元素e，L的长度加1.
    ElemType * newbase,* q,* p;
    if ( (i < 1) || (i > L->length+1)) return ERROR;
    if (L->length >= L->listsize){
        newbase = (ElemType*)realloc(L->elem,(L->listsize+LIST_INIT_SIZE)*sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LIST_INIT_SIZE;
    }
    q = &(L->elem[i-1]);
    for (p = &(L->elem[L->length-1]); p >= q;--p) *(p+1) = *p;
    *q = e;
    L->length++;
    return OK;
}

Status ListDelete_Sq(Sqlist *L, int i, ElemType *e){
//删除L的第i个数据元素，并用e返回其值，L的长度减1.
    ElemType *p,*q;
    if ( (i < 1) || (i > L->length)) return ERROR;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length - 1;
    for (++p;p <= q;++p) *(p-1) = *p;
    L->length--;
    return OK;
}

Status ListTraverse_Sq(Sqlist L,void(Visit)(ElemType)){
//依次对L的每个数据元素调用函数visit().一旦visit()失败，则操作失败。
    int i;
    for (i=0;i<L.length;i++)Visit(L.elem[i]);
    return OK;
}