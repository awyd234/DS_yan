#include <stdio.h>
#include <stdlib.h>

#include "sq_stack.h"
#include "type_def.h"

Status InitStack(SqStack &S){
	// 构造一个空栈S
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		return ERROR;	//存储分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}// InitStack

Status DestroyStack(SqStack &S){
	// 销毁栈S，S不再存在
	S.base = NULL;
	free(S.base);
	return OK;
}// DestroyStack

Status ClearStack(SqStack &S){
	// 把S置为空栈
	S.base = S.top;
	S.stacksize = 0;
	return OK;
}// ClearStack

Status StackEmpty(SqStack S){
	// 若栈S为空栈，则返回TRUE，否则返回FALSE
	return (S.base == S.top) ? TRUE : FALSE;
}// StackEmpty

int StackLength(SqStack S){
	// 返回S的元素个数，即栈的长度
	return (S.top - S.base);
}// StackLength

Status GetTop(SqStack S, SElemType &e){
	// 若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回ERROR
	if (S.top == S.base)
		return ERROR;
	e = *(S.top - 1);
	return OK;
}// GetTop

Status Push(SqStack &S, SElemType e){
	// 插入元素e为新的栈顶元素
	if (S.top - S.base >= S.stacksize){	//栈满，追加存储空间
		S.base = (SElemType *)realloc(S.base, 
					(S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base)	//存储分配失败
			return ERROR;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	* S.top++ = e;
	return OK;
}// Push

Status Pop(SqStack &S, SElemType &e){
	// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base)
		return ERROR;
	e = * --S.top;
	return OK;
}// Pop

Status StackTraverse(SqStack S, Status(*visit)(SElemType)){
	// 从栈底到栈顶依次对栈中每个元素调用函数visit(),一旦visit()失败，则操作失败
	SElemType *p;
	p = S.base;
	while (p != S.top){
		if (!visit(*p)) return ERROR;
		p++;
	}
	printf("\n");
	return OK;
}// StackTraverse

Status Visit_Display_Char(SElemType e){
	// 打印字符e
	printf("%c ", e);
	return OK;
}// Visit_Display_Char

Status Visit_Display_Int(SElemType e){
	// 打印整型变量e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int