#include<stdio.h>
#include<stdlib.h>
#include "list.h"
void printElem(ElemType e){
    printf("%d\n",e);
}
int main(void)
{
    Sqlist L;
    ElemType e;
    int i;
    printf("初始化线性表L\n");
    InitList_Sq(&L);
    if (ListEmptpy_Sq(L)) printf("L为空表\n");
    for (i=1;i<=8;i++){
        printf("在线性表第%d个位置插入%d\n",i,i*2);
        ListInsert_Sq(&L,i,i*2);
    }
    ListTraverse_Sq(L,printElem);
    return 0;
}  