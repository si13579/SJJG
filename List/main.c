#include<stdio.h>
#include<stdlib.h>
#include "list.h"
void printElem(ElemType e){
    printf("%d\n",e);
}
Status CmpGreater(ElemType data,ElemType e){
    return data > e ? True : Flase;
}
int main(void)
{
    Sqlist L;
    ElemType e;
    int i;
    printf("初始化线性表L\n");
    InitList_Sq(&L);
    if (ListEmptpy_Sq(L)) printf("L为空表\n");
    else
        printf("L不为空表\n");
    for (i=1;i<=8;i++){
        printf("在线性表第%d个位置插入%d\n",i,i*2);
        ListInsert_Sq(&L,i,i*2);
    }
    printf("L中的元素为：\n");
    ListTraverse_Sq(L,printElem);

    int len = ListLength_Sq(L);
    printf("L的长度为: %d\n",len);

    printf("删除前的元素为\n：");
    ListTraverse_Sq(L,printElem);
    
    printf("尝试删除L中的第6个元素\n");
    if (ListDelete_Sq(&L,6,&e) == OK) printf("删除成功\n");
    else 
        printf("删除失败\n");

    printf("删除后的元素为:\n");
    ListTraverse_Sq(L,printElem);

    GetElem_Sq(L,4,&e);
    printf("L中的第四个元素为: %d\n",e);

    int a = LocateElem_Sq(L,7,CmpGreater);
    printf("L中第一个大于7的元素值是%d\n",L.elem[a-1]);

    ElemType cur_e = 6;
    if (PriorElem_Sq(L,cur_e,&e) == OK){
        printf("%d的前驱为%d\n",cur_e,e);
    }   
    else 
        printf("%d的前驱不存在\n",cur_e);

    //ElemType cur_e = 6;
    if (NextElem_Sq(L,cur_e,&e) == OK){
        printf("%d的后继为%d\n",cur_e,e);
    }   
    else 
        printf("%d的后继不存在\n",cur_e);

    printf("清空L前\n");
    if (ListEmptpy_Sq(L) == True) printf("L为空\n");
    else
        printf("L不为空\n");
    
    ClearList_Sq(&L);

    printf("清空L后\n");
    if (ListEmptpy_Sq(L) == True) printf("L为空\n");
    else
        printf("L不为空\n");

    printf("销毁L前\n");
    if (L.elem != NULL) printf("L存在\n");
    else
        printf("L不存在\n");
    
    DestoryList_Sq(&L);
    printf("销毁L后\n");
    if (L.elem != NULL) printf("L存在\n");
    else
        printf("L不存在\n");
    
    return 0;
}  