#include<stdio.h>
#include<stdlib.h>
#include"list.h"
int main(){
    Sqlist L;
    InitList_Sq(&L);
    ListInSert_Sq(&L,1,5);
    return 0;
}