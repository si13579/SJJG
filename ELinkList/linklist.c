#include"lisklist.h"
/*
分配由p指向的值为e的结点，并返回OK；
若分配失败，则返回ERROR
*/
Status MakeNode(Link *p, ElemType e){
    if (!p)return ERROR;
    (*p) = (Link)malloc(sizeof(LNode));
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}
/*
释放p所指结点
*/
void FreeNode(Link *p){
    if(!p || *p == NULL)return;
    free(*p);
    (*p) = NULL;
}

/*
构造一个空的线性链表L
*/
Status InitList(LinkList *L){
    Link p;
    if(L == NULL)return ERROR;
    p = (Link)malloc(sizeof(LNode));
    p->next = NULL;
    (*L).head = (*L).tail = p;
    (*L).len = 0;
    return OK;
}

/*
销毁线性链表L，L不再存在
*/
Status DestoryList(LinkList *L){
    if (L==NULL || (*L).head == NULL)return ERROR;
    ClearList(L);
    free((*L).head);
    (*L).head = (*L).tail = NULL;
    return OK;
}

/*
将线性链表L重置为空表，并释放原链表的结点空间
*/
Status ClearList(LinkList *L){
    Link p,q;
    if (L == NULL || (*L).head == NULL || (*L).len <= 0)return ERROR;
    p = (*L).head->next;
    while (p){
        q = p->next;
        free(p);
        p = q;
    }
    (*L).head->next = NULL;
    (*L).tail = (*L).head;
    (*L).len = 0;
    return OK;
}

/*
将s结点插入到h结点后面，成为h后面第一个结点
*/
Status InsFirst(LinkList *L,Link h,Link s){
    if (L == NULL || (*L).head == NULL || h == NULL || s == NULL )return ERROR;
    s->next = h->next;
    h->next = s;

    if (h == (*L).tail) (*L).tail = h->next;
    (*L).len++;
    return OK;

}

/*
删除h结点后的第一个结点，并用q存储被删除结点的引用
*/
Status DelFirst(LinkList *L,Link h,Link *q){
    if (L == NULL || (*L).head == NULL || h == NULL || q == NULL)return ERROR;

    if (h->next == NULL)return ERROR;

    *q = h->next;
    h->next = (*q)->next;

    (*q)->next = NULL;

    if (h->next == NULL)(*L).tail = h;
    (*L).len--;
    return OK;
}

/*
将指针s所指（彼此以指针相链）的一串结点链接在线性链表L的最后一个结点之后，
并改变链表L的尾指针指向新的尾结点
*/
Status Append(LinkList *L,Link s){
    int count;
    if (L == NULL || (*L).head == NULL || s == NULL)return ERROR;
    count = 0;
    (*L).tail->next = s;
    while (s){
        (*L).tail = s;
        s = s->next;
        count++;
    }
    (*L).len += count;
    return OK;
}

/*
删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
*/
Status Remove(LinkList *L,Link *q){
    Link p;
    if (L == NULL || (*L).head == NULL || q == NULL)return ERROR;
    if ((*L).len == 0)return ERROR;
    *q = (*L).tail;
    p = (*L).head;
    while (p->next != (*L).tail){
        p = p->next;
    }
    p->next = NULL;
    (*L).tail = p;
    (*L).len--;
    return OK;
}

/*
已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之前，
并修改指针p指向新插入的结点
*/
Status InsBefore(LinkList *L,Link *p,Link s){
    Link pre;
    if (L == NULL || (*L).head == NULL || p == NULL || s == NULL)return ERROR;
    pre = (*L).head;
    while (pre != NULL && pre->next != (*p)){
        pre = pre->next;
    }
    while (pre == NULL)return ERROR;
    s->next = (*p);
    pre->next = s;
    (*p) = s;
    (*L).len++;
    return OK;
}

/*
已知p指向线性链表L中的一个结点，将s所指结点插入在p所指结点之后，
并修改指针p指向新插入的结点
*/
Status InsAfter(LinkList *L,Link *p,Link s){
    Link pre;
    if (L == NULL || (*L).head == NULL || p == NULL || s == NULL)return ERROR;
    pre = (*L).head;
    while (pre != NULL && pre != (*p)){
        pre = pre->next;
    }
    if (pre == NULL )return ERROR;
    if (*p = (*L).tail) (*L).tail = s;
    s->next = (*p)->next;
    (*p)->next = s;
    *p = s;
    (*L).len++;

    return OK;
}

/*
已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
*/
Status SetCurElem(Link p,ElemType e){
    if (p == NULL)return ERROR;
    p->data = e;
    return OK;
}

/*
已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
*/
ElemType GetCurElem(Link p){
    return p->data;
}

/*
若线性链表L为空表，则返回TRUE
否则返回FALSE
*/
Status ListEmpty(LinkList L){
    if(L.len <= 0)return TRUE;
    return FALSE;
}

/*
返回线性链表L中元素个数
*/
int ListLength(LinkList L){
    return L.len;
}

/*
返回线性链表L中头结点的位置
*/
Position GetHead(LinkList L){
    return L.head;
}

/*
返回线性链表L中最后一个结点的位置
*/
Position GetLast(LinkList L){
    return L.tail;
}

/*
已知p指向线性链表L中的一个结点，
返回p所指结点的直接前驱的位置
若无前驱，则返回NULL
*/
Position PriorPos(LinkList L,Link p){
    Link pre;
    if (L.head == NULL || p == NULL)return ERROR;
    pre = L.head;
    if (pre->next = p)return ERROR;
    while (pre != NULL && pre->next != p)
        pre = pre->next;
    return pre;
}

/*
已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置
若无后继，则返回NULL
*/
Position NextPos(LinkList L,Link p){
    if (L.head == NULL || p == NULL)return ERROR;
    if (p->next == NULL)return ERROR;
    return p->next;
}

/*
返回p指示线性链表L中第i个结点的位置并返回Ok，i值不合法时返回ERROR
*/
Status LocatePos(LinkList L,int i,Link *p){
    int j;
    Link pre;
    if (i < 0 || i > L.len)return ERROR;
    if (L.head == NULL)return ERROR;
    pre = L.head;
    j = 0;
    while (pre && j < i){
        pre = pre->next;
        j++;
    }
    if(pre == NULL)return ERROR;
    *p = pre;
    return OK;
}

/*
返回线性链表L中第一个与e满足函数compare（）判定关系的元素的位置
若不存在这样的元素，则返回NULL
*/
Position LocateElem(LinkList L,ElemType e,Status(compare)(ElemType,ElemType)){
    Position p;
    if (L.len <=0)return ERROR;
    p = L.head->next;
    while ( p && !compare(p->data,e))
        p = p->next;
    return p;
}

/*
依次对L的每个元素调用函数visit（）。一旦visit（）失败，则操作失败
*/
Status ListTraverse(LinkList L,Status(visit)()){
    Link p;
    if(L.len <= 0)return ERROR;
    p = L.head->next;
    while (p){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}


/*
在带头结点的单链线性链表L的第i个元素之前插入e
*/
Status ListInsert_L(LinkList *L,int i,ElemType e){
    Link h,s;
    if (L == NULL || (*L).head == NULL)return ERROR;
    if (i < 1 || i > (*L).len+1)return ERROR;
    if (!LocatePos(*L,i-1,&h))return ERROR;
    if (!MakeNode(&s,e))return ERROR;
    if (!InsFirst(L,h,s))return ERROR;
    return OK;

}

/*
删除链表第i个位置上的元素，并将被删除元素存储到e中
删除成功则返回OK，否则返回error
*/
Status ListDelete_L(LinkList *L,int i,ElemType *e){
    Link h,s;
    if (L == NULL || (*L).head == NULL)return ERROR;
    if (i < 1 || i > (*L).len)return ERROR;
    if (!LocatePos(*L,i-1,&h))return ERROR;
    if (!DelFirst(L,h,&s))return ERROR;
    *e = s->data;
    FreeNode(&s);
    return OK;
}

/*
已知单链线性表La和Lb的元素按值非递减排列
归并La和Lb得到新的单链线性表Lc
*/
Status MerageList_L(LinkList *La,LinkList *Lb,LinkList *Lc,int(compare)(ElemType,ElemType)){
    Link ha,hb,qa,qb,q;
    ElemType a,b;
    if (!InitList(Lc))return ERROR;
    ha = GetHead(*La);
    hb = GetHead(*Lb);
    if (ha == NULL || hb == NULL)return ERROR;
    qa = NextPos(*La,ha);
    qb = NextPos(*Lb,hb);
    while (qa && qb){
        a = GetCurElem(qa);
        b = GetCurElem(qb);
        if (compare(a,b) <= 0){
            DelFirst(La,ha,&q);
            Append(Lc,q);
            qa = NextPos(*La,ha);
        }
        else {
            DelFirst(Lb,hb,&q);
            Append(Lc,q);
            qb = NextPos(*Lb,hb);
        }
    }
    if (qa)Append(Lc,qa);
    else
        Append(Lc,qb);
    FreeNode(&(La->head));
    FreeNode(&(Lb->head));
    La->tail = NULL;
    Lb->tail = NULL;
    La->len = 0;
    Lb->len = 0;
    return OK;
}
