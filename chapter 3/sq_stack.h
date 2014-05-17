#ifndef _SQ_STACK_H_
#define _SQ_STACK_H_

//------------定义顺序栈------------
#include "type_def.h"

typedef struct {
	SElemType *base;	//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;		//栈顶指针
	int stacksize;		//当前已分配的储存空间，以元素为单位
}SqStack;

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, SElemType &e);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S, SElemType &e);
Status Visit_Display_Char(SElemType e);
Status Visit_Display_Int(SElemType e);
Status StackTraverse(SqStack S, Status(*visit)(SElemType));

#endif
