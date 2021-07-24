#include"polynomial.h"
/*
内存分配
为线性链表申请一个结点，并存入指定的数据e。
*/
Status MakeNode(Link *p,ElemType e){
    if (p == NULL)return ERROR;
    *p = (Link)malloc(sizeof(LNode));
    if (*p == NULL)return ERROR;
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}

/*
内存回收
释放线性链表中指定的结点
*/
void FreeNode(Link *p){
    if (p == NULL || *p == NULL)return;
    free(*p);
    *p = NULL;
}

/*
初始化
初始化成功返回OK，否则返回ERROR
*/
Status InitList(LinkList *L){
    Link p;
    if (L == NULL)exit(OVERFLOW);
    p = (Link)malloc(sizeof(LNode));
    p->next = NULL;
    (*L).head = (*L).tail = p;
    return OK;
}

/*
销毁（结构）
释放链表所占内存
*/
Status DestoryList(LinkList *L){
    if (L == NULL || (*L).head == NULL)return ERROR;
    ClearList(L);
    free((*L).head);
    (*L).head = (*L).tail = NULL;
    return OK;
}

/*
置空（内容）
这里需要释放链表中非头结点处的空间
*/
Status ClearList(LinkList *L){
    Link p,q;
    if (L == NULL || (*L).head == NULL || (*L).len <= 0)return ERROR;
    p = (*L).head->next;
    while (p != NULL){
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
计数
返回链表中包含的有效元素的数量
*/
int ListLength(LinkList L){
    return L.len;
}
   
/*
查找
这里首先会查找与元素e满足compare（）==0的元素，如果找到，使用q存储其引用，并返回true
如果不存在上述引用，则查找首个与元素e满足compare()>0的前驱，并返回FALSE
如果链表中的元素均大于e，q存储头结点引用
如果链表中的元素均小于e，q存储尾结点引用
其他情形下，会将q置空
*/
Status LocateElem(LinkList L,ElemType e,Position *q,Status(Compare)(ElemType,ElemType)){
    Position pre,p;
    *q = NULL;
    if (L.head == NULL)return FALSE;
    pre = L.head;
    p = pre->next;

    while (p != NULL && Compare(p->data,e) < 0){
        pre = p;
        p = p->next;
    }
    if (p != NULL && Compare(p->data,e)==0){
        *q = p;
        return TRUE;
    }
    *q = pre;
    return FALSE;
}

/*
取值
获取结点p的元素值
*/
ElemType GetCurElem(Link p){
    ElemType e;
    if ( p == NULL){
        e.coef = 0.0f;
        e.expn = -1;
        return e;
    }
    return p->data;
}

/*
设值
为结点p设置元素值
*/
Status SetCurElem(Link p,ElemType e){
    if (p == NULL)return ERROR;
    p->data = e;
    return OK;
}

/*
头结点
获取头结点引用
*/
Position GetHead(LinkList L){
    return L.head;
}

/*
后继
获取结点p的后继，如果不存在，则返回NULL
*/
Position NextPos(LinkList L,Link p){
    if (L.head == NULL)return NULL;
    if (p == NULL)return NULL;
    return p->next;
}

/*
插入
将s结点插入到h结点后面，成为h后面的第一个结点
*/
Status InsFirst(LinkList *L,Link h,Link s){
    if (L == NULL || h == NULL || s == NULL)return ERROR;
    s->next = h->next;
    h->next = s;
    if (h == (*L).tail)(*L).tail = h->next;
    (*L).len++;
    return OK;
}

/*
删除
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
向尾部添加
将s所指的一串结点链接链表L后面
*/
Status Append(LinkList *L,Link s){
    int count;
    if (L == NULL || (*L).head == NULL || s == NULL)return ERROR;
    count = 0;
    (*L).tail->next = s;
    while (s != NULL){
        (*L).tail = s;
        s= s->next;
        count++;
    }
    (*L).len += count;
    return OK;
}

/*
创建
根据输入的系数和指数，创建项数为m的一元多项式
*/
void CreatPolyn(Polynomial *P,int m,char *path){
    int i;
    ElemType e;
    Position h,q;
    Link s;
    FILE *fp;
    int readFromConsole = path == NULL || strcmp(path,"") == 0;
    InitList(P);
    h = GetHead(*P);

    e.coef = 0.0f;
    e.expn = -1;
    SetCurElem(h,e);

    if (readFromConsole){
        fp = fopen(path,"r");
        if (fp == NULL){
            exit(ERROR);
        }
    }
    if (!readFromConsole){
        printf("请输入 %d 个元素: \n",m);
    }
    for (i = 1;i <= m;i++){
        if (!readFromConsole){
            printf("请输入第 %d 组系数和指数：",i);
            scanf("%f%d",&(e.coef),&(e.expn));
        }
        else
            fscanf(fp,"%f%d",&(e.coef),&(e.expn));
        
        if (LocateElem(*P,e,&q,Cmp) == FALSE && q != NULL){
            if (MakeNode(&s,e) == OK)
                InsFirst(P,q,s);
        }

    }
    if (readFromConsole)
        fclose(fp);
}

/*
销毁
销毁一元多项式
*/
void DestoryPolyn(Polynomial *P){
    DestoryList(P);
}

/*
计数
返回一元多项式的项数。
*/
int PolynLength(Polynomial P){
    return ListLength(P);
}

/*
加法
一元多项式加法Pa=Pa+Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void AddPolyn(Polynomial *Pa,Polynomial *Pb){
    Position ha,hb;
    Position qa,qb;
    ElemType a,b;
    float sum;

    ha = GetHead(*Pa);
    hb = GetHead(*Pb);
    qa = NextPos(*Pa,ha);
    qb = NextPos(*Pb,hb);

    while (qa && qb){
        a = GetCurElem(qa);
        b = GetCurElem(qb);
        switch(Cmp(a,b)){
            case -1:{
                ha = qa;
                qa = NextPos(*Pa,qa);
            }
            break;

            case 0:{
                sum = a.coef + b.coef;
                if (sum != 0.0){
                    qa->data.coef = sum;
                    ha = qa;
                }
                else{
                    DelFirst(Pa,ha,&qa);
                    FreeNode(&qa);
                }
                DelFirst(Pb,hb,&qb);
                FreeNode(&qb);

                qa = NextPos(*Pa,ha);
                qb = NextPos(*Pb,hb);
            }
            break;

            case 1:{
                DelFirst(Pb,hb,&qb);
                InsFirst(Pa,ha,qb);
                ha = NextPos(*Pa,ha);
                qb = NextPos(*Pb,hb);
            }
            break;
        }
    }
    if (qb != NULL)Append(Pa,qb);
    FreeNode(&hb);
    (*Pb).head = (*Pb).tail = NULL;
    (*Pb).len = 0;

}

/*
减法
一元多项式减法Pa=Pa-Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void SubtractPolyn(Polynomial *Pa,Polynomial *Pb){
    Position ha,hb;
    Position qa,qb;
    Position r;
    ElemType a,b;
    float sum;

    ha = GetHead(*Pa);
    hb = GetHead(*Pb);

    qa = NextPos(*Pa,ha);
    qb = NextPos(*Pb,hb);

    while (qa && qb){
        a = GetCurElem(qa);
        b = GetCurElem(qb);
        switch(Cmp(a,b)){
            case -1:{
                ha = qa;
                qa = NextPos(*Pa,ha);
            }
            break;

            case 0:{
                sum = a.coef - b.coef;
                if (sum != 0.0){
                    qa->data.coef = sum;
                    ha = qa;
                }
                else {
                    DelFirst(Pa,ha,&qa);
                    FreeNode(&qa);
                }
                DelFirst(Pb,hb,&qb);
                FreeNode(&qb);

                qa = NextPos(*Pa,ha);
                qb = NextPos(*Pb,hb);
            }
            break;

            case 1:{
                DelFirst(Pb,ha,&qb);
                qb->data.coef = -qb->data.coef;

                InsFirst(Pa,ha,qb);
                ha = NextPos(*Pa,ha);
                qb = NextPos(*Pb,hb);
            }
            break;
        }
    }

    if (qb != NULL){
        for (r = qb; r != NULL; r = r->next)
            r->data.coef = -r->data.coef;
        Append(Pa,qb);
    }
    FreeNode(&hb);
    (*Pb).head = (*Pb).tail = NULL;
    (*Pb).len = 0;
}

/*
乘法
一元多项式乘法Pa=Pa*Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void MultiplyPoyn(Polynomial *Pa,Polynomial *Pb){
    Polynomial Pc,Ptmp;
    int i,j,la,lb;
    Position ha,hb;
    Position qa,qb;
    Link s;
    ElemType e;
    la = PolynLength(*Pa);
    lb = PolynLength(*Pb);

    ha = GetHead(*Pa);
    hb = GetHead(*Pb);

    InitList(&Pc);

    for (i = 1;i <= la;i++){
        InitList(&Ptmp);
        DelFirst(Pa,ha,qa);
        for (j = 1,qb = NextPos(*Pb,hb); j <=lb;j++,qb = NextPos(*Pb,qb) ){
            e.coef = qa->data.coef * qb->data.coef;
            e.expn = qa->data.expn + qb->data.expn;

            MakeNode(&s,e);
            Append(&Ptmp,s);
        }
        AddPolyn(&Pc,&Ptmp);
    }
    AddPolyn(Pa,&Pc);
    DestoryPolyn(Pb);
}

/*
输出
打印输出一元多项式
*/
void PrintPolyn(Polynomial P){
    int i;
    Link p;
    p = P.head->next;
    for (i = 1;i<= P.len;i++){
        if (p->data.coef == 0.0f)
            continue;
        if (i == 1){
            printf("%g",p->data.coef);
        }
        else {
            if (p->data.coef > 0){
                printf(" + ");
                printf("%g",p->data.coef);
            }
            else {
                printf(" - ");
                printf("%g",p->data.coef);
            }
        }
        if (p->data.expn){
            printf("x");
            if (p->data.expn != 1){
                printf("^%d",p->data.expn);
            }
        }
        p = p->next;
    }
    printf("\n");
}

/*
比较
比较c1项和c2项指数大小
*/
int Cmp(ElemType c1,ElemType c2){
    int i = c1.expn - c2.expn;
    if (i<0)return -1;
    else if (i == 0)return 0;
    else    
        return 1;
}