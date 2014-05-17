#include <stdio.h>
#include <stdlib.h>

#include "sq_stack.h"
#include "type_def.h"

Status InitStack(SqStack &S){
	// ����һ����ջS
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		return ERROR;	//�洢����ʧ��
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}// InitStack

Status DestroyStack(SqStack &S){
	// ����ջS��S���ٴ���
	S.base = NULL;
	free(S.base);
	return OK;
}// DestroyStack

Status ClearStack(SqStack &S){
	// ��S��Ϊ��ջ
	S.base = S.top;
	S.stacksize = 0;
	return OK;
}// ClearStack

Status StackEmpty(SqStack S){
	// ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
	return (S.base == S.top) ? TRUE : FALSE;
}// StackEmpty

int StackLength(SqStack S){
	// ����S��Ԫ�ظ�������ջ�ĳ���
	return (S.top - S.base);
}// StackLength

Status GetTop(SqStack S, SElemType &e){
	// ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if (S.top == S.base)
		return ERROR;
	e = *(S.top - 1);
	return OK;
}// GetTop

Status Push(SqStack &S, SElemType e){
	// ����Ԫ��eΪ�µ�ջ��Ԫ��
	if (S.top - S.base >= S.stacksize){	//ջ����׷�Ӵ洢�ռ�
		S.base = (SElemType *)realloc(S.base, 
					(S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base)	//�洢����ʧ��
			return ERROR;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	* S.top++ = e;
	return OK;
}// Push

Status Pop(SqStack &S, SElemType &e){
	// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base)
		return ERROR;
	e = * --S.top;
	return OK;
}// Pop

Status StackTraverse(SqStack S, Status(*visit)(SElemType)){
	// ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit(),һ��visit()ʧ�ܣ������ʧ��
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
	// ��ӡ�ַ�e
	printf("%c ", e);
	return OK;
}// Visit_Display_Char

Status Visit_Display_Int(SElemType e){
	// ��ӡ���ͱ���e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int