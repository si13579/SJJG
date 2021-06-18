#include"List.h"

Status InitList_Sq(Sqlist *L){
    //����һ���µ����Ա�L
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (L->elem) exit(OVERFLOW); //�洢����ʧ��
    L->length = 0;                //�ձ���Ϊ0
    L->listsize = LIST_INIT_SIZE; //��ʼ�洢����
    return OK;   
}

void DestoryList_Sq(Sqlist *L){
//�������Ա�L
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
}

void ClearList_Sq(Sqlist *L){
//�����Ա�L����Ϊ�ձ�
    L->length = 0;
}

Status ListEmptpy_Sq(Sqlist L){
//��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
    return L.length == 0 ? True : Flase;
}
Status ListLength_Sq(Sqlist L){
//�������Ա�L��Ԫ�ظ���
    return L.length;
}

Status GetElem_Sq(Sqlist L,int i,ElemType *e){
//��e����L�е�i������Ԫ�ص�ֵ
    if (i < 1 || i > L.length)
        return ERROR;
    else
        *e = L.elem[i-1];
    return OK;
}
Status LocateElem_Sq(Sqlist L,ElemType e,Status(Compare)(ElemType,ElemType)){
//����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��
//������������Ԫ�ز����ڣ��򷵻�ֵΪ0.
    int i = 1;
    ElemType * p = L.elem;
    while (i <= L.length && !Compare(*p++,e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

Status PriorElem_Sq(Sqlist L,ElemType cur_e,ElemType * pre_e){
//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����
//�������ʧ�ܣ�pre_e�޶��塣
    int i = 1;
    if (L.elem[0] != cur_e){
        while (i < L.length && L.elem[i] != cur_e)
            i++;
        if (i < L.length){
            *pre_e = L.elem[i-1];
            return OK;
        }
    }
    return ERROR;
}

Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType * next_e){
//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�
//next_e�޶���
    int i = L.length-1;
    if (L.elem[i] != cur_e){
        while (i > 0 && L.elem[i] != cur_e)
            i--;
        if (i > 0){
            *next_e = L.elem[i+1];
            return OK;
        }
    }
    return ERROR;
}

Status ListInsert_Sq(Sqlist *L, int i, ElemType e){
//��L�е�i��λ��֮ǰ�����µ�Ԫ��e��L�ĳ��ȼ�1.
    ElemType * newbase,* q,* p;
    if ( (i < 1) || (i > L->length+1)) return ERROR;
    if (L->length >= L->listsize){
        newbase = (ElemType*)realloc(L->elem,(L->listsize+LIST_INIT_SIZE)*sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LIST_INIT_SIZE;
    }
    q = &(L->elem[i-1]);
    for (p = &(L->elem[L->length-1]); p >= q;--p) *(p+1) = *p;
    *q = e;
    L->length++;
    return OK;
}

Status ListDelete_Sq(Sqlist *L, int i, ElemType *e){
//ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1.
    ElemType *p,*q;
    if ( (i < 1) || (i > L->length)) return ERROR;
    p = &(L->elem[i-1]);
    *e = *p;
    q = L->elem + L->length - 1;
    for (++p;p <= q;++p) *(p-1) = *p;
    L->length--;
    return OK;
}

Status ListTraverse_Sq(Sqlist L,void(Visit)(ElemType)){
//���ζ�L��ÿ������Ԫ�ص��ú���visit().һ��visit()ʧ�ܣ������ʧ�ܡ�
    int i;
    for (i=0;i<L.length;i++)Visit(L.elem[i]);
    return OK;
}