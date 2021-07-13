#include"triplet.h"
/*
操作结果：构造了三元组T，元素e1，e2，e3分别被赋以参数v1，v2，v3的值
*/
Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3){
    *T = (Triplet)malloc(3*sizeof(ElemType));
    if (!(*T)) exit(OVERFLOW);
    (*T)[0] = v1;
    (*T)[1] = v2;
    (*T)[2] = v3;
    return OK;
}

/*
操作结果：三元组T被销毁
*/
Status DestoryTriplet(Triplet *T){
    free(*T);
    (*T) = NULL;
    return OK;
}

/*
初始条件：三元组T已存在，1 <= i <= 3.
操作结果：用e返回T的第i元的值。
*/
Status Get(Triplet T,int i,ElemType *e){
    if (i<1 || i > 3) return ERROR;
    *e = T[i-1];
    return OK;
}

/*
初始条件：三元组T已存在，1 <= i <= 3;
操作结果： 改变T的第i元的值为e。
*/
Status Put(Triplet *T,int i,ElemType e){
    if (i<1 || i > 3) return ERROR;
    (*T)[i-1] = e;
    return OK;
}


/*
初始条件：三元组T已存在
操作结果：如果T的3个元素按升序排列，则返回1，否则返回0；
*/
Status IsAscending(Triplet T){
    return (T[0] >= T[1]) && (T[1] >= T[2]);
}

/*
初始条件：三元组T已存在
操作结果：如果T的3个元素按降序排列，则返回1，否则返回0.
*/
Status IsDescending(Triplet T){
    return (T[0] <= T[1]) && (T[1] <= T[2]);
}

/*
初始条件：三元组T已存在
操作结果：用e返回T的3个元素最大的值
*/
Status Max(Triplet T,ElemType *e){
    if (!T) return ERROR;
    *e = (T[0] >= T[1]) ? (T[0] >= T[2] ? T[0] : T[2])
                        : (T[1] >= T[2] ? T[1] : T[2]); 
    return OK;
}

/*
初始条件：三元组T已经存在
操作结果：用e返回三个元素中最小的值
*/
Status Min(Triplet T,ElemType *e){
    if (!T) return ERROR;
    *e = (T[0] <= T[1]) ? (T[0] <= T[2] ? T[0] : T[2])
                        : (T[1] <= T[2] ? T[1] : T[2]);
    return OK;
}