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
    if (p == L)return ERROR;
    *e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;

}

/*
初始化
初始化成功则返回OK，否则返回ERROR
*/
Status InitList_DuL(DuLinkList *L){
    *L = (DuLinkList)malloc(sizeof(DuLNode));
    if (*L == NULL)exit(OVERFLOW);
    (*L)->next = (*L)->prior = (*L);
    return OK;
}

/*
销毁（结构）
释放双向链表所占内存
*/
Status DestoryList_DuL(DuLinkList *L){
    if (L == NULL || *L == NULL)return ERROR;
    ClearList_DuL(*L);
    free(*L);
    *L = NULL;
    return OK;
}

/*
置空（内容）
这里需要释放双向链表中非头结点的空间
*/
Status ClearList_DuL(DuLinkList L){
    DuLinkList p,q;
    if (L == NULL)return ERROR;

    p = L->next;
    while (p != L){
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L;
    return OK;
}

/*
判空
判断双向链表中是否包含有有效数据
返回值
*/
Status ListEmpty_DuL(DuLinkList L){
    if (L != NULL && L->next == L && L->prior == L)
        return TRUE;
    else 
        return FALSE;
}

/*
计数
返回双向循环链表中有效元素的数量
*/
int ListLength_DuL(DuLinkList L){
    DuLinkList p;
    if (L == NULL || L->next == L || L->prior == L)return 0;
    int i = 0;
    p = L->next;
    while (p != L){
        p = p->next;
        i++;
    }
    return i;
}

/*
取值
获取双向循环链表中第i个元素，将其存储到e中
如果可以找到，返回OK，否则，返回ERROR
*/
Status GetElem_DuL(DuLinkList L,int i,ElemType *e){
    DuLinkList p;
    int j;
    if (L == NULL || L->next == L || L->prior == L)return ERROR;
    p = L;
    j = 0;
    while (p->next != L && j < i-1){
        p = p->next;
        ++j;
    }
    if (p->next == L || j > i-1)return ERROR;
    *e = p->next->data;
    return OK;
}


/*
查找
返回双向循环链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0
*/
Status LocateElem_DuL(DuLinkList L,ElemType e,Status(Compare)(ElemType,ElemType)){
    int i;
    DuLinkList p;
    if (L == NULL || L->next == L || L->prior == L)return ERROR;
    i = 1;
    p = L->next;
    while (p!= L && !Compare(p->data,e)){
        i++;
        p = p->next;
    }
    if (p!= L)return i;
    return 0;
}

/*
前驱
获取元素cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_DuL(DuLinkList L,ElemType cur_e,ElemType *pre_e){
    DuLinkList p;
    if (L == NULL || L->next == NULL || L->prior == L)return ERROR;
    p = L->next;
    if (p->data == cur_e)return ERROR;
    p = p->next;
    while (p != L && p->data != cur_e)
        p = p->next;
    if (p == L)return ERROR;
    *pre_e = p->prior->data;
    return OK;
}

/*
后继
获取元素cur_e的后继
如果存在，则将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_DuL(DuLinkList L,ElemType cur_e,ElemType *next_e){
    DuLinkList p;
    if (L== NULL || L->next == L || L->prior == L)return ERROR;
    p = L->next;
    while (p->next != L && p->data != cur_e)
        p = p->next;
    if (p->next == L)return ERROR;
    *next_e = p->next->data;
    return OK;
}

/*
遍历
用visit函数访问双向循环链表L
*/
void ListTraverse_DuL(DuLinkList L,void(Visit)(ElemType)){
    DuLinkList p;
    if (L == NULL || L->next == L || L->prior == L)return ERROR;
    p = L->next;
    while (p != L){
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
}