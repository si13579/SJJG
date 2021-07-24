#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2

typedef int Status;

typedef struct {
    float coef; //系数
    int expn;   //指数
}term,ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*Link,*Position;

typedef struct{
    Link head,tail;
    int len;
}LinkList;

typedef LinkList Polynomial;


/*
内存分配
为线性链表申请一个结点，并存入指定的数据e。
*/
Status MakeNode(Link *p,ElemType e);

/*
内存回收
释放线性链表中指定的结点
*/
void FreeNode(Link *p);

/*
初始化
初始化成功返回OK，否则返回ERROR
*/
Status InitList(LinkList *L);

/*
销毁（结构）
释放链表所占内存
*/
Status DestoryList(LinkList *L);

/*
置空（内容）
这里需要释放链表中非头结点处的空间
*/
Status ClearList(LinkList *L);

/*
计数
返回链表中包含的有效元素的数量
*/
int ListLength(LinkList L);

/*
查找
这里首先会查找与元素e满足compare（）==0的元素，如果找到，使用q存储其引用，并返回true
如果不存在上述引用，则查找首个与元素e满足compare()>0的前驱，并返回FALSE
如果链表中的元素均大于e，q存储头结点引用
如果链表中的元素均小于e，q存储尾结点引用
其他情形下，会将q置空
*/
Status LocateElem(LinkList L,ElemType e,Position *q,Status(Compare)(ElemType,ElemType));

/*
取值
获取结点p的元素值
*/
ElemType GetCurElem(Link p);

/*
设值
为结点p设置元素值
*/
Status SetCurElem(Link p,ElemType e);

/*
头结点
获取头结点引用
*/
Position GetHead(LinkList L);

/*
后继
获取结点p的后继，如果不存在，则返回NULL
*/
Position NextPos(LinkList L,Link p);

/*
插入
将s结点插入到h结点后面，成为h后面的第一个结点
*/
Status InsFirst(LinkList *L,Link h,Link s);

/*
删除
删除h结点后的第一个结点，并用q存储被删除结点的引用
*/
Status DelFirst(LinkList *L,Link h,Link *q);

/*
向尾部添加
将s所指的一串结点链接链表L后面
*/
Status Append(LinkList *L,Link s);

/*
创建
根据输入的系数和指数，创建项数为m的一元多项式
*/
void CreatPolyn(Polynomial *P,int m,char *path);

/*
销毁
销毁一元多项式
*/
void DestoryPolyn(Polynomial *P);

/*
计数
返回一元多项式的项数。
*/
int PolynLength(Polynomial P);

/*
加法
一元多项式加法Pa=Pa+Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void AddPolyn(Polynomial *Pa,Polynomial *Pb);

/*
减法
一元多项式减法Pa=Pa-Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void SubtractPolyn(Polynomial *Pa,Polynomial *Pb);

/*
乘法
一元多项式乘法Pa=Pa*Pb
计算完成后，计算结果存到Pa中，并将Pb销毁
*/
void MultiplyPoyn(Polynomial *Pa,Polynomial *Pb);

/*
输出
打印输出一元多项式
*/
void PrintPolyn(Polynomial P);

/*
比较
比较c1项和c2项指数大小
*/
int Cmp(ElemType c1,ElemType c2);

#endif