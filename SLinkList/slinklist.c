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
void InitSpace_SL(SLinkList *space){
    int i;
    for (i = 0; i < MAXSIZE - 1;i++){
        (*space)[i].cur = i+1;
    }
    (*space)[MAXSIZE-1].cur = 0;
}

/*
若备用空间链表非空，则返回分配的结点下标
*/
int Malloc_SL(SLinkList *space){
    int i;
    i = (*space)[0].cur;
    if((*space)[0].cur) (*space)[0].cur = (*space)[i].cur;
    return i;
}

/*
将下标为k的空闲结点回收到备用链表
*/
void Free_SL(SLinkList *space,int k){
    (*space)[k].cur = (*space)[0].cur;
    (*space)[0].cur = k;
}

/*
依次输入集合A和B的元素，在一维数组sapce中建立表示集合(A-B)并(B-A)的静态链表，S为其头指针。
假设备用空间足够大，space[0].cur为其头指针。
*/
void difference(SLinkList *space,int *S){
    int r,j,i,m,n;
    InitSpace_SL(*space);
    (*S) = Malloc_SL(*space); //S头结点指针（游标）
    r = (*S);  //r指向最后结点
    scanf("%d,%d",m,n);
    for (j = 0; j < m; j++){
        i = Malloc_SL(*space);
        scanf("%d",space[i]->data);
        space[r]->cur = i;
        r = i;
    }
    space[r]->cur = 0;

    int b,p,k;
    for (i = 0; i < n; i++){
        scanf("%d",&b);
        p = (*S);
        k = space[*S]->cur;
        while ( k != space[r]->cur && space[k]->data != b){
            p = k;
            k = space[k]->cur;
        }

        if (k == space[r]->cur){
            i = Malloc_SL(*space);
            space[i]->data = b;
            space[i]->cur = space[r]->cur;
            space[r]->cur = i;
        }
        else {
            space[p]->cur = space[k]->cur;
            Free_SL(*space,k);
            if (r == k)r=p;
        }
   }

}