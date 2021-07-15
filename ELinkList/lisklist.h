#ifndef LINKLIST_H_
#define LINKLIST_H_

#define OK  1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}*Link,*Position;

typedef struct{
    Link head,tail;
    int len;
}LinkList;





#endif