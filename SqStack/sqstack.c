#include"sqstack.h"
/*
初始化
构造一个空栈。初始化成功则返回Ok，否则返回ERROR
*/
Status InitStack(SqStack *S){
    if (S == NULL)return ERROR;
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if ((*S).base == NULL)exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

/*
销毁（结构）
释放顺序栈所占内存
*/
Status DestoryStack(SqStack *S){
    if (S == NULL)return ERROR;
    free((*S).base);
    (*S).base = NULL;
    (*S).top = NULL;
    return OK;
}

/*
置空（内容）
只是清理顺序栈中存储的数据，不释放顺序栈所占内存
*/
Status ClearStack(SqStack *S){
    if (S == NULL || (*S).base == NULL)return ERROR;
    (*S).top = (*S).base;
    return OK;
}

/*
判空
判断顺序栈中是否包含有效数据
*/
Status StackEmpty(SqStack S){
    if (S.top == S.base)return TRUE;
    else 
        return FALSE;
}

/*
计数
返回S的元素个数，即栈的长度
*/
int StackLength(SqStack S){
    if (S.base == NULL)return 0;
    return (int)(S.top-S.base);
}

/*
取值
若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
*/
Status GetTop(SqStack S,SElemType *e){
    if (S.base == NULL || S.top == S.base)return ERROR;
    *e = *(S.top-1);
    return OK;
}

/*
入栈
将元素e压入栈顶
*/
Status Push(SqStack *S,SElemType e){
    if (S == NULL || (*S).base == NULL)return ERROR;
    if ((*S).top - (*S).base >= (*S).stacksize){
        (*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCRMENT)*sizeof(SElemType));
        if((*S).base == NULL){
            exit(OVERFLOW);
        }
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCRMENT;
    }
    *(S->top++)=e;
    return OK;
}

/*
出栈
将栈顶元素弹出，并用e接收
*/
Status Pop(SqStack *S,SElemType *e){
    if (S == NULL || S->base == NULL)return ERROR;
    *e = *(--(S->top));
    return OK;
}

/*
遍历
用visit函数访问顺序栈S
*/
Status StackTraverse(SqStack S,void(visit)(SElemType)){
    SElemType *p = S.base;
    if (S.base == NULL)return ERROR;
    while (p < S.top)
        visit(*p++);
    printf("\n");
    return OK;
}

/*
对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数
*/
void conversion(){
    SqStack S;
    SElemType e;
    InitStack(&S);
    int N;
    scanf("%d",&N);
    while (N){
        Push(&S,N%8);
        N /= 8;
    }
    while (!StackEmpty(S)){
        Pop(&S,&e);
        printf("%d",e);
    }
    printf("\n");
}

/*
行编辑程序，模拟编辑文本时的退格与清空行的操作
*/
void LineEdit(){
    SqStack S;
    SElemType e;
    InitStack(&S);
    char ch = getchar();
    while (ch != EOF){
        while (ch != EOF && ch != '\n'){
            switch(ch){
                case '#':
                    Pop(&S,&e);
                    break;
                case '@':
                    ClearStack(&S);
                default:
                    Push(&S,ch);
            }
            ch = getchar();
    }
    ClearStack(&S);
    if (ch != EOF)ch = getchar();
}
DestoryStack(&S);
}

/*
 * ████████ 算法3.2 ████████
 *
 * 行编辑程序，模拟编辑文本时的退格与清空行的操作。
 *
 *【注】
 * 教材使用的是控制台输入，这里为了便于测试，直接改为从形参接收参数
 */
/*
void LineEdit(const char buffer[]) {
    SqStack S;                        //接收输入的字符
    SElemType e;
    int i;
    char ch;
    
    // 初始化栈
    InitStack(&S);
    
    i = 0;
    ch = buffer[i++];
    
    // 如果未达文本末尾
    while(ch != EOF) {
        // 如果未达文本末尾，且本行未结束（未遇到换行）
        while(ch != EOF && ch != '\n') {
            switch(ch) {
                case '#':
                    Pop(&S, &e);    // 遇到'#'表示删除一个字符
                    break;
                case '@':
                    ClearStack(&S); // 遇到'@'表示清空当前行
                    break;
                default :
                    Push(&S, ch);   // 有效字符入栈
            }
            
            // 识别下一个字符
            ch = buffer[i++];
        }
        
        // 清空之前输出当前栈的内容，此处教材上没有
        StackTraverse(S, Print);
        
        // 清空改行的缓冲区
        ClearStack(&S);
        
        // 如果未到文本末尾，说明遇到了'\n'，即该行结束了
        if(ch != EOF) {
            // 进入下一行
            ch = buffer[i++];
        }
    }
    
    // 已经到了文本末尾，输出目前栈中的元素，此处教材上没有
    StackTraverse(S, Print);
    
    // 销毁栈
    DestroyStack(&S);
}
*/
/*
// 测试函数，打印元素
void Print(SElemType e) {
    printf("%c", e);
}
*/