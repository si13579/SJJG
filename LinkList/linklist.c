#include"linklist.h"

/*
当第i个元素存在时，其值赋给e并返回Ok，否则返回ERROR
*/
Status GetElem_L(LinkList L,int i,ElemType *e){
    int j = 1;
    LNode *p = L->next;
    while (p && j < i){
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    *e = p->data;
    return Ok;
}

/*
在带头结点的单链线性表L中第i个位置之前插入元素e
*/
Status ListInsert_L(LinkList *L,int i,ElemType e){
    LinkList p,q;
    int j = 0;
    p = *L;
    while (p && j < i -1 ){
        p = p->next;
        j++;
    }
    if (!p || j > i - 1)return ERROR;
    q = (LinkList)malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return Ok;
}

/*
在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
*/
Status ListDelete_L(LinkList *L,int i,ElemType *e){
    LinkList p,q;
    int j = 0;
    p = (*L);
    while (p->next && j < i - 1){
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return Ok;
}

/*
逆位序输入n个元素的值，建立带表头结点的单链线性表L
*/
void CreateList_L(LinkList *L,int n){
    *L = (LinkList)malloc(sizeof(LNode));
    LinkList p;
    (*L)->next = NULL;
    int i;
    for (i=n;n>0;i--){
        p = (LinkList)malloc(sizeof(LNode));
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

/*
已知单链线性表La和Lb的元素按值非递减排列
归并La和Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
*/
void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc){
    LinkList pa,pb,pc;
    pa = (*La)->next;
    pb = (*Lb)->next;
    Lc = pc = (*La);
    while (pa && pb){
        if (pa->data <= pa->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}