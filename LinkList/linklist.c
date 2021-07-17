#include"linklist.h"

/*
初始化
初始化成功则返回OK,否则返回ERROR
*/
Status InitList_L(LinkList *L){
    (*L) = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL)exit(OVERFLOW);
    (*L)->next = NULL;
    return Ok;
}

/*
销毁（结构）
释放链表所占内存
*/
Status DestoryList_L(LinkList *L){
    LinkList p;

    if (L == NULL || *L == NULL)return ERROR;

    p = *L;
    while (p){
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }
    *L = NULL;
    return Ok;
}

/*
置空（内容）
这里需要释放链表中非头结点处的空间
*/
Status ClearList_L(LinkList L){
    LinkList pre,p;
    if (L == NULL)return ERROR;
    p = L->next;
    while (p){
        pre = p;
        p = p->next;
        free(pre);
    }
    L->next = NULL;
    return Ok;
}

/*
判空
判断链表中是否包含有效数据
返回值
TRUE：链表为空
FALSE：链表不为空
*/
Status ListEmpty_L(LinkList L){
    if (L != NULL && L->next == NULL){
        return True;
    }
    else
        return False;
}

/*
计数
返回链表包含的有效元素的数量
*/
int ListLength_L(LinkList L){
    LinkList p;
    int i;
    if (L == NULL || L->next == NULL)return ERROR;
    i = 0;
    p = L->next;
    while (p){
        i++;
        p = p->next;
    }
    return i;
}


/*
查找
返回链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0
元素e是Compare函数第二个形参
*/
int LocateElem_L(LinkList L,ElemType e,Status(Compare)(ElemType,ElemType)){
    int i;
    LinkList p;
    if (L == NULL || L->next == NULL)return 0;
    i = 1;
    p = L->next;
    while (p != NULL && !Compare(p->data,e)){
        p = p->next;
        i++;
    }
    if (p != NULL){
        return i;
    }
    else
        return 0;
}

/*
前驱
获取cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_L(LinkList L,ElemType cur_e,ElemType *pre_e){
    LinkList p,prior;
    if (L == NULL || L->next == NULL)return ERROR;
    p = L->next;
    if (p->data == cur_e)return ERROR;
    while (p && p->data != cur_e){
        prior = p;
        p = p->next;
    }
    if (p){
        *pre_e = prior->data;
        return Ok;
    }
    return ERROR;
}

/*
后继
获取元素cur_e的后继
如果存在，将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_L(LinkList L,ElemType cur_e,ElemType *next_e){
    LinkList p;
    if (L == NULL || L->next == NULL)
        return ERROR;
    p = L->next;
    while (p->next != NULL && p->data != cur_e){
        p = p->next;
    }
    if (p->next != NULL){
        *next_e = p->next->data;
        return Ok;
    }
    return ERROR;
}


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
Status ListInsert_L(LinkList L,int i,ElemType e){
    LinkList p,q;
    int j = 0;
    p = L;
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
Status ListDelete_L(LinkList L,int i,ElemType *e){
    LinkList p,q;
    int j = 0;
    p = L;
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
    (*Lc) = pc = (*La);
    while (pa && pb){
        if (pa->data <= pb->data){
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
    free(*Lb);
}

/*
遍历
用visit函数访问链表L
*/
void ListTravese(LinkList L,void(Visit)(ElemType)){
    LinkList p;
    if (L == NULL || L->next == NULL) return;
    p = L->next;
    while (p){
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
}

/*
头插法创建链表
*/
Status CreateListHead_L(LinkList *L,int n,char *path){
    int i;
    LinkList p;
    FILE *fp;
    int readFromConsole;
    readFromConsole = path == NULL || strcmp(path,"") == 0;
    if (!readFromConsole) {
        *L = (LinkList)malloc(sizeof(LNode));
        (*L)->next = NULL;

        printf("请输入%d个元素：",n);

        for (i = 0;i<n;i++){
            p = (LinkList)malloc(sizeof(LNode));
            scanf("%d",&(p->data));

            p->next = (*L)->next;
            (*L)->next = p;
        }
    }
    else {
        fp = fopen(path,"r");
        if (!fp)return ERROR;

        *L = (LinkList)malloc(sizeof(LNode));
        (*L)->next = NULL;

        for (i = 0;i<n;i++){
            p = (LinkList)malloc(sizeof(LNode));
            fscanf(fp,"%d",&(p->data));

            p->next = (*L)->next;
            (*L)->next = p;
        }
        fclose(fp);
    }
    return Ok;
}

/*
尾插法创建链表
*/
Status CreateListTail_L(LinkList *L,int n,char *path){
    int i;
    LinkList p,q;
    FILE *fp;
    int readFromConsole;
    readFromConsole = path == NULL || strcmp(path,"") == 0;

    if (!readFromConsole) {
        *L = (LinkList)malloc(sizeof(LNode));
        (*L)->next = NULL;

        printf("请输入%d个元素：",n);

        for (i = 0,q = (*L);i<n;i++){
            p = (LinkList)malloc(sizeof(LNode));
            scanf("%d",&(p->data));

            q->next = p;
            q = q->next;
        }
        q->next = NULL;
    }
    else {
        fp = fopen(path,"r");
        if (!fp)return ERROR;

        *L = (LinkList)malloc(sizeof(LNode));
        (*L)->next = NULL;

        for (i = 0,q = (*L);i<n;i++){
            p = (LinkList)malloc(sizeof(LNode));
            fscanf(fp,"%d",&(p->data));

            q->next = p;
            q = q->next;
        }
        q->next = NULL;
        fclose(fp);
    }
    return Ok;
}