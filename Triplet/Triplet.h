#include<stdio.h>
#include<stdlib.h>
#define True 1
#define Flase 0
#define OK 1
#define ERROR 0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int Status;


typedef int ElemType;
typedef ElemType * Triplet;

Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3);
Status DestoryTriplet(Triplet *T);
Status Get(Triplet T,int i,ElemType *e);
Status Put(Triplet *T,int i,ElemType e);
Status IsAscending (Triplet T);
Status IsDescengding(Triplet T);
Status Max(Triplet T, ElemType *e);
Status Min(Triplet T, ElemType *e);