#include<stdio.h>
#include"slinklist.h"
int main(){
    SLinkList L;
    int S;
    int i ;
    InistList_SL(L,&S);
    ListInsert_SL(L,S,1,5);
    //printf("%d\n",L[0].data);
    return 0;
}