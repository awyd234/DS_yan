#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

Status CreateBiTree(BiTree &T){
	// �������������������н���ֵ��һ���ַ������ո��ַ���ʾ����
	// ������������ʾ�Ķ�����T
	char ch;
	scanf("%c",&ch);
	//getchar();		// ��ȡ�س�
	if (ch == ' '){
		T = NULL;
	} else{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;				// ���ɸ����
		CreateBiTree(T->lchild);	// ����������
		CreateBiTree(T->rchild);	// ����������
	}
	return OK;
}// CreateBiTree

Status PreOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e)){
	// ���ö���������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	if (T){
		if (Visit(T->data))
			if (PreOrderTraverse_Recur(T->lchild, Visit))
				if (PreOrderTraverse_Recur(T->rchild, Visit))
					return OK;
		return ERROR;
	}else return OK;
}// PreOrderTraverse_Recur

Status InOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e)){
	// ���ö���������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	if (T){
		if (InOrderTraverse_Recur(T->lchild, Visit))
			if (Visit(T->data))
				if (InOrderTraverse_Recur(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else return OK;
}// InOrderTraverse_Recur

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e)){
	// ���ö���������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	// �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);
	while (!StackEmpty(S)){
		while (!GetTop(S, p) && p) Push(S, p->lchild);
		Pop(S, p);
		if (!StackEmpty(S)){
			Pop(S, p);
			if (!Visit(p->data)) return ERROR;
			Push(S, p->rchild);
		}// if
	}// while
	return OK;
}// InOrderTraverse

Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e)){
	// ���ö���������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	// �������������T�ķǵݹ��㷨2����ÿ������Ԫ�ص��ú���Visit
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)){
		if (p){
			Push(S, p);
			p = p->lchild;
		} else{
			Pop(S, p);
			if (!Visit(p->data)) return ERROR;
			p = p->rchild;
		}// else
	}// while
	return OK;
}// InOrderTraverse2

Status PostOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e)){
	// ���ö���������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	// �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	if (T){
		if (PostOrderTraverse_Recur(T->lchild, Visit))
			if (PostOrderTraverse_Recur(T->rchild, Visit))
				if (Visit(T->data))
					return OK;
		return ERROR;
	}
	else return OK;
}// PostOrderTraverse_Recur

Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));

Status PrintElement(TElemType e){
	// ���Ԫ��e��ֵ
	printf("%c" , e);
	return OK;
}// PrintElement
