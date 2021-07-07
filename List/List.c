#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*
构造一个空的线性表L
*/
Status InitList_Sq(Sqlist *L){
    (*L).Elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if ((*L).Elem == NULL) exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}

/*
初始条件：线性表L已存在
操作结果：销毁线性表L
*/

Status DestoryList_Sq(Sqlist *L){
    if (L == NULL && (*L).Elem == NULL) return ERROR;
    free((*L).Elem);
    (*L).Elem = NULL;
    (*L).length = 0;
    (*L).listsize = 0;
    return OK;
}

/*
初始条件：线性表L已存在
操作结果：将L重置为空表
*/
Status ClearList_Sq(Sqlist *L){
    if (L == NULL && (*L).Elem == NULL) return ERROR;
    (*L).length = 0;
    return OK;
}

/*
初始条件：线性表L已存在
操作结果：若L为空表，则返回True，否则返回False
*/
Status ListEmpty_Sq(Sqlist L){
    return (L.length==0) ? TRUE : FALSE;
}

/*
初始条件：线性表L已存在
操作结果：返回线性表L中元素的个数
*/
Status ListLength_Sq(Sqlist L){
    return L.length;
}

/*
初始条件：线性表L已存在，i为线性表L的元素位序，1 <= i <= Listlength_Sq(L);
操作结果：用e返回L中第i个元素的值
*/
Status GetElem_Sq(Sqlist L,int i,ElemType *e){
    if (i < 1 || i > L.length) return ERROR;
    *e = L.Elem[i-1];
    return OK; 
}

/*
初始条件：线性表L已存在，compare()是数据元素判定函数
操作结果：返回L中第一个与e满足关系compar()的数据元素的位序。若这样的元素不存在，则返回0；
*/
Status LocateElem_Sq(Sqlist L, ElemType e,Status(compare)(ElemType,ElemType)){
    int i = 1;
    ElemType *p;
    if (L.Elem == NULL) return ERROR;
    p = L.Elem;
    while ( i <= L.length && !compare(*p++,e))
        i++;
    if (i <= L.length) return i;
    else
        return 0;
}

/*
初始条件：线性表L已存在
操作结果：若cur_e是L中的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
*/
Status PriorElem_Sq(Sqlist L,ElemType cur_e,ElemType *pre_e){
    int i = 0;
    if (L.Elem == NULL || L.length < 2) return ERROR;
    while (i < L.length && L.Elem[i] != cur_e)
        i++;
    if (i == 0 || i >= L.length) return ERROR;
    *pre_e = L.Elem[i-1];
    return OK;
}

/*
初始条件：线性表L已存在
操作结果：若cur_e是L中的数据元素，且不是最后一个，则用next_e返回它的后驱，否则操作失败，next_e无定义
*/
Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType *next_e){
    int i = 0;
    if (L.Elem == NULL || L.length < 2) return ERROR;
    while (i < L.length && L.Elem[i] != cur_e)
        i++;
    if (i >= L.length - 1) return ERROR;
    *next_e = L.Elem[i+1];
    return OK;
}

/*
初始条件：线性表L已存在，i为线性表L的元素位序，1 <= i <= Listlength_Sq(L)+1;
操作结果：在L中第i个位置插入新的数据元素e，L的长度加1；
*/
Status ListInSert_Sq(Sqlist *L,int i, ElemType e){
   if ( i < 1 || i > L->length+1) return ERROR;
   ElemType *p,*q,*newbase;
   if (L->length >= L->listsize){
       newbase = (ElemType *)realloc(L->Elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
       if (!newbase)exit(OVERFLOW);
       L->Elem = newbase;
       L->listsize += LISTINCREMENT;
   }
   p = &(L->Elem[i-1]);
   for (q = &(L->Elem[L->length-1]); q >= p; q--) *(q+1) = *q;
   *p = e;
   L->length++;
   return OK;
    
}

/*
初始条件：线性表L已存在且非空，i为线性表L的元素位序，1 <= i <= ListLength_Sq(L);
操作结果：删除线性表L的第i个元素，并用e返回其值，L的长度减1。
*/
Status ListDelete_Sq(Sqlist *L,int i, ElemType *e){
    if (i < 1 || i > L->length) return ERROR;
    ElemType *p,*q;
    p = &(L->Elem[i-1]);
    *e = *p;
    q = L->Elem + L->length - 1;
    for (++p;q >= p;++p) *(p-1) = *p;
    L->length--;
    return OK;
}

void visit(ElemType e){
    printf("%d\n",e);
}
/*
初始条件：线性表L已存在
操作结果：依次对L的每个元素调用函数visit()。一旦visit()失败，则操作失败
*/
Status ListTraverse_Sq(Sqlist L,void(visit)(ElemType)){
    int i;
    for (i=0;i < L.length;i++)
        visit(L.Elem[i]);
    printf("\n");
    return OK;
}

Status compare(ElemType e1,ElemType e2){
    return (e1 == e2);
}
/*
将所有在线性表Lb但不在La中的数据元素插入到La中
*/
void Union_Sq(Sqlist *La,Sqlist Lb){
    ElemType e;
    int La_len,Lb_len;
    La_len = ListLength_Sq(*La);
    Lb_len = ListLength_Sq(Lb);
    int i;
    for (i = 0;i<Lb_len;i++){
        GetElem_Sq(Lb,i+1,&e);
        if (!LocateElem_Sq(*La,e,compare))
            ListInSert_Sq(La,++La_len,e);
    }
}

/*
已知线性表La和Lb中的元素按值非递减排列
归并La和Lb得到新的线性表Lc，Lc中的数据元素也按值非递减排列
*/
void MergeList_Sq1(Sqlist La,Sqlist Lb,Sqlist * Lc){
    InitList_Sq(Lc);
    int La_len,Lb_len;
    La_len = ListLength_Sq(La);
    Lb_len = ListLength_Sq(Lb);
    int i,j,k;
    i = j = k =1;
    ElemType ai,bi;
    while ((j <= La_len) && (k <= Lb_len)){
        GetElem_Sq(La,j,&ai);
        GetElem_Sq(La,k,&bi);
        if (ai <= bi){
            ListInSert_Sq(Lc,i++,ai);
            j++;
        }
        else{
            ListInSert_Sq(Lc,i++,bi);
            k++;
        }
    }
    while (j <= La_len) {
        GetElem_Sq(La,j++,&ai);
        ListInSert_Sq(Lc,i++,ai);
    }
    while (k <= Lb_len) {
        GetElem_Sq(Lb,j++,&bi);
        ListInSert_Sq(Lc,i++,bi);
    }
}

/*
已知线性表La和Lb中的元素按值非递减排列
归并La和Lb得到新的线性表Lc，Lc中的数据元素也按值非递减排列
*/
void MergeList_Sq2(Sqlist La,Sqlist Lb,Sqlist * Lc){
    ElemType *pa,*pb,*pc;
    ElemType *pa_last,*pb_last;
    pa = La.Elem;
    pb = Lb.Elem;
    Lc->listsize = Lc->length = La.length + Lb.length;
    pc = Lc->Elem = (ElemType *)malloc(Lc->listsize*sizeof(ElemType));
    if (!Lc->Elem) exit(OVERFLOW);
    pa_last = pa + La.length - 1;
    pb_last = pb + Lb.length - 1;
    while (pa <= pa_last && pb <= pb_last){
        if (*pa <= *pb) *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last) *pc++ = *pa++;
    while (pb <= pb_last) *pc++ = *pb++;
}
