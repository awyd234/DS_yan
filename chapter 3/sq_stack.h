#ifndef _SQ_STACK_H_
#define _SQ_STACK_H_

//------------����˳��ջ------------
#include "type_def.h"

typedef struct {
	SElemType *base;	//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;		//ջ��ָ��
	int stacksize;		//��ǰ�ѷ���Ĵ���ռ䣬��Ԫ��Ϊ��λ
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
