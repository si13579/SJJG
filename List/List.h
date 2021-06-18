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
#define LIST_INIT_SIZE  100 //���Ա�洢�ռ�ĳ�ʼ������
#define LISTINCRMENT    10  //���Ա�洢�ռ�ķ�������

typedef struct 
{
    ElemType * elem;    //�洢�ռ��ַ
    int length;         //��ǰ����
    int listsize;       //��ǰ����Ĵ洢��������sizeof(ElemType)
}Sqlist;

Status InitList_Sq(Sqlist *L);
//����һ���յ����Ա�L

void DestoryList_Sq(Sqlist *L);
//�������Ա�L

void ClearList_Sq(Sqlist *L);
//�����Ա�L����Ϊ�ձ�

Status ListEmptpy_Sq(Sqlist L);
//��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE

Status ListLength_Sq(Sqlist L);
//�������Ա�L��Ԫ�ظ���

Status GetElem_Sq(Sqlist L,int i,ElemType *e);
//��e����L�е�i������Ԫ�ص�ֵ

Status LocateElem_Sq(Sqlist L,ElemType e,Status(Compare)(ElemType,ElemType));
//����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��
//������������Ԫ�ز����ڣ��򷵻�ֵΪ0.

Status PriorElem_Sq(Sqlist L,ElemType e,ElemType * pre_e);
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����
//�������ʧ�ܣ�pre_e�޶��塣

Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType * next_e);
//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�
//next_e�޶���

Status ListInsert_Sq(Sqlist *L, int i, ElemType e);
//��L�е�i��λ��֮ǰ�����µ�Ԫ��e��L�ĳ��ȼ�1.

Status ListDelete_Sq(Sqlist *L, int i, ElemType *e);
//ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1.

Status ListTraverse_Sq(Sqlist L,void(Visit)(ElemType));
//���ζ�L��ÿ������Ԫ�ص��ú���visit().һ��visit()ʧ�ܣ������ʧ�ܡ�