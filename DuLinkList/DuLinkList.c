#include"DuLinkList.h"
/*
在L中确定插入位置指针p
*/
static DuLinkList GetElemP_DuL(DuLinkList L,int i){
    DuLinkList p;

    if (L == NULL)return NULL;

    if (i < 1)return NULL;

    p = L;
    int count = 0;
    while (p->next != L && count < i){
        p = p->next;
        count++;
    }

    if (count == i)return p;
    if (count+1 < i)return ERROR;
    return L;
}

/*
在带头结点的双链循环线性表L中第i个位置之前插入元素e
i的合法值为1 <= i <= 表长+1
*/
Status ListInsert_DuL(DuLinkList L,int i,ElemType e){
    DuLinkList p,s;
    if (!(p = GetElemP_DuL(L,i)))return ERROR;
    s = (DuLinkList)malloc(sizeof(DuLNode));
    if(!s) return ERROR;
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    p->prior = s;
    s->next = p;
    return OK;
}

/*
删除带头结点的双链循环线性表L的第i个元素，i的合法值为1 <= i <= 表长
*/
Status ListDelete_DuL(DuLinkList L,int i,ElemType *e){
    DuLinkList p;
    if (!(p = GetElemP_DuL(L,i))) return ERROR;
    *e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;

}

