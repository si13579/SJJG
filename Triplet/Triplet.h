#ifndef _TRIPLET_H_
#define _TRIPLET_H_
#include<stdio.h>
#include<stdlib.h>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE      -1
#define OVERFLOW        -2

typedef int Status;
typedef int ElemType;
typedef ElemType * Triplet;

Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3);
/*
操作结果：构造了三元组T，元素e1，e2，e3分别被赋以参数v1，v2，v3的值
*/

Status DestoryTriplet(Triplet *T);
/*
操作结果：三元组T被销毁
*/

Status Get(Triplet T,int i,ElemType *e);
/*
初始条件：三元组T已存在，1 <= i <= 3.
操作结果：用e返回T的第i元的值。
*/

Status Put(Triplet *T,int i,ElemType e);
/*
初始条件：三元组T已存在，1 <= i <= 3;
操作结果： 改变T的第i元的值为e。
*/

Status IsAscending(Triplet T);
/*
初始条件：三元组T已存在
操作结果：如果T的3个元素按升序排列，则返回1，否则返回0；
*/

Status IsDescending(Triplet T);
/*
初始条件：三元组T已存在
操作结果：如果T的3个元素按降序排列，则返回1，否则返回0.
*/

Status Max(Triplet T,ElemType *e);
/*
初始条件：三元组T已存在
操作结果：用e返回T的3个元素最大的值
*/

Status Min(Triplet T,ElemType *e);
/*
初始条件：三元组T已经存在
操作结果：用e返回三个元素中最小的值
*/
#endif
