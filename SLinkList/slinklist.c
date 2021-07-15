#include"slinklist.h"
/*
在静态单链线性表L中查找第一个值为e的元素
若找到，则返回它在L中的位序，否则返回0
*/
int LocateElem_SL(SLinkList L,ElemType e){
    int i;
    i = L[0].cur;
    while (i && L[i].data != e)
        i = L[i].cur;
    return i;
}


/*
将一维数组space中各分量链成一个备用链表，sapce[0].cur为头指针
“0”表示空指针
*/
void InitSpace_SL(SLinkList space){
    int i;
    for (i = 0; i < MAXSIZE - 1;i++){
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;
}

/*
若备用空间链表非空，则返回分配的结点下标
*/
int Malloc_SL(SLinkList space){
    int i;
    i = space[0].cur;
    if(space[0].cur) space[0].cur = space[i].cur;
    return i;
}

/*
将下标为k的空闲结点回收到备用链表
*/
void Free_SL(SLinkList space,int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

/*
依次输入集合A和B的元素，在一维数组sapce中建立表示集合(A-B)并(B-A)的静态链表，S为其头指针。
假设备用空间足够大，space[0].cur为其头指针。
*/
void difference(SLinkList space,int *S){
    int r,j,i,m,n;
    InitSpace_SL(space);
    (*S) = Malloc_SL(space); //S头结点指针（游标）
    r = (*S);  //r指向最后结点
    scanf("%d,%d",&m,&n);
    for (j = 0; j < m; j++){
        i = Malloc_SL(space);
        scanf("%d",&(space[i].data));
        space[r].data = i;
        r = i;
    }
    space[r].cur = 0;

    int b,p,k;
    for (i = 0; i < n; i++){
        scanf("%d",&b);
        p = (*S);
        k = space[*S].cur;
        while ( k != space[r].cur && space[k].data != b){
            p = k;
            k = space[k].cur;
        }

        if (k == space[r].cur){
            i = Malloc_SL(space);
            space[i].data = b;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        }
        else {
            space[p].cur = space[k].cur;
            Free_SL(space,k);
            if (r == k)r=p;
        }
   }

}


//静态链表操作
/*
初始化
先初始化备用空间，而后从备用空间中申请头结点的空间，进而完成链表的初始化
初始化成功则使用S存储头结点索引，且返回OK，否则返回ERROR
*/
Status InistList_SL(SLinkList space,int *S){
    int index;
    InitSpace_SL(space);
    index = Malloc_SL(space);
    if (!index)return ERROR;
    space[index].cur = 0;
    *S = index;
    return OK;
}

/*
销毁（结构）
释放静态链表所占内存，即将静态链表所有结点空间移入备用空间列表中。
*/
Status DestoryList_SL(SLinkList space,int *S){
    int cur;
    if (S == NULL || *S == 0)return ERROR;
    while (*S){
        cur = space[*S].cur;
        Free_SL(space,*S);
        *S = cur;
    }
    return OK;
}

/*
置空（内容）
这里需要释放静态链表中非头结点处的空间
*/
Status ClearList_SL(SLinkList space,int S){
    int P;
    int cur;
    if (!S)return ERROR;
    P = space[S].cur;
    while (P){
        cur = space[P].cur;
        Free_SL(space,P);
        P = cur;
    }
    space[S].cur = 0;
    return OK;
}

/*
判空
判断静态链表中是否包含有效数据
返回值
TRUE：  静态链表为空
FALSE： 静态链表不为空
*/
Status ListEmpty_SL(SLinkList space,int S){
    if (S != 0 && space[S].cur == 0)return TRUE;
    else 
        return FALSE;
}

/*
计数
返回静态链表包含的有效元素的数量
*/
int ListLength_SL(SLinkList space,int S){
    int count;
    if (S == 0 || space[S].cur == 0)return 0;

    S = space[S].cur;
    count = 0;
    while (S){
        count++;
        S = space[S].cur;
    }
    return count;
}

/*
取值
获取静态链表中第i个元素，将其存储到e中
如果可以找到，返回OK，否则，返回ERROR
*/
Status GetElem_SL(SLinkList space, int S,int i, ElemType * e){
    int count;
    if (S == 0 || space[S].cur == 0)return ERROR;
    S = space[S].cur;
    count = 0;
    while (S && count < i-1){
        S = space[S].cur;
        count++;
    }
    if (!S || count > i-1)return ERROR;
    *e = space[S].data;
    return OK;
}

/*
查找
返回静态链表中首个与e满足Compare关系的元素位序
如果不存在这样的元素，则返回0.
*/
int LocateElem(SLinkList space,int S,ElemType e,Status(Compare)(ElemType,ElemType)){
    int i,p;
    if (S == 0 || space[S].cur == 0)return ERROR;

    i = 1;
    p = space[S].cur;
    while (p && !Compare(space[p].data,e)){
        i++;
        p = space[p].cur;
    }
    if(p)return i;
    else
        return 0;
}

/*
前驱
获取元素cur_e的前驱
如果存在，将其存储到pre_e中，返回OK
如果不存在，则返回ERROR
*/
Status PriorElem_SL(SLinkList space, int S,ElemType cur_e,ElemType *pre_e){
    int pre,next;
    if (S == 0 || space[S].cur == 0)return ERROR;
    pre = space[S].cur;
    if (space[pre].data == cur_e)return ERROR;
    next = space[pre].cur;
    while (next && space[next].data != cur_e){
        pre = next;
        next = space[next].cur;
    }
    if (next){
        *pre_e = space[pre].data;
        return OK;
    }
    return ERROR;
}

/*
后继
获取元素cur_e的后继
如果存在，将其存储到next_e中，返回OK
如果不存在，则返回ERROR
*/
Status NextElem_SL(SLinkList space,int S, ElemType cur_e,ElemType *next_e){
    int pre;
    if (S == 0 || space[S].cur == 0)return ERROR;
    pre = space[S].cur;
    while (space[pre].cur && space[pre].data != cur_e){
        pre = space[pre].cur;
    }
    if (space[pre].cur){
        *next_e = space[space[pre].cur].data;
        return OK;
    }
    return ERROR;

}

/*
插入
向静态链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR
*/
Status ListInsert_SL(SLinkList space, int S,int i,ElemType e){
    int p,s;
    int j;
    if (!S)return ERROR;
    p = S;
    j = 0;
    while (p && j < i-1){
        p = space[p].cur;
        j++;
    }
    if (!p || j > i-1)return ERROR;

    s = Malloc_SL(space);
    space[s].data = e;
    space[s].cur = space[p].cur;
    space[p].cur = s;

    return OK;
}

/*
删除
删除静态链表第i个位置上的元素，并将被删元素存储到e中
删除成功则返回OK，否则返回ERROR
*/
Status ListDelete_SL(SLinkList space, int S,int i,ElemType *e){
    int p,q;
    int j;
    if (!S)return ERROR;
    p = S;
    j = 0;
    while (space[p].cur && j < i-1){
        p = space[p].cur;
        j++;
    }
    if (space[p].cur == 0 || j > i - 1){
        return ERROR;
    }
    q = space[p].cur;
    space[p].cur = space[q].cur;
    *e = space[q].data;
    Free_SL(space,q);

    return OK;
}
static void Visit(ElemType e){
    printf("%d\n",e);
}
/*
遍历
用visit函数访问静态链表
*/
void ListTraverse_SL(SLinkList space,int S,void(Visit)(ElemType)){
    int p;
    if (S == 0 || space[S].cur == 0)return ;
    p = space[S].cur;
    while (p){
        Visit(space[p].data);
        p = space[p].cur;
    }
    printf("\n");
}

// 以图形化形式输出结构
void PrintList_SL(SLinkList space,int S){
     int i = 0;
    
    printf("==== 备用空间 ====\n");
    while(i < 20) {
        printf("%2d    | %2d | %2d |\n", i, space[i].data, space[i].cur);
        i = space[i].cur;
    }
    
    printf("==== 静态链表 ====\n");
    i = S;
    while(i>0 && i < 20) {
        printf("%2d    | %2d | %2d |\n", i, space[i].data, space[i].cur);
        i = space[i].cur;
    }
}
