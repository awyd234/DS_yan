#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status CreateBiThrTree(BiThrTree &T){
	// �����������������������н���ֵ��һ���ַ������ո��ַ���ʾ����
	// ������������ʾ������������T
	TElemType ch;
	#if CHAR				// �ο��α����ϸ�����
		scanf("%c", &ch);
	#else
		scanf("%d", &ch);
	#endif
	if (ch == ' '){
		T = NULL;
	} else{
		if (!(T = (BiThrNode *)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data = ch;
		CreateBiThrTree(T->lchild);	// ����������
		if (T->lchild)				// ������
			T->LTag = Link;
		CreateBiThrTree(T->rchild);	// ����������
		if (T->rchild)				// ���Һ���
			T->RTag = Link;
	}
	return OK;
}// CreateBiThrTree

Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e)){
	// Tָ��ͷ��㣬ͷ��������lchildָ������
	// �����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
	BiThrTree p = T->lchild;	// pָ������
	while (p != T){				// �������������ʱ��p==T
		while (p->LTag == Link) p = p->lchild;
		if (!Visit(p->data)) return ERROR;		// ������������Ϊ�յĽ��
		while (p->RTag == Thread&&p->rchild != T){
			p = p->rchild;		// ���ʺ�̽��
			Visit(p->data);	
		}
		p = p->rchild;
	}
	return OK;
}// InOrderTraverse_Thr

BiThrTree pre;
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	// �������������T��������������������Thrtָ��ͷ���
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag = Link;		// ��ͷ���
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;	// ��ָ���ָ
	if (!T){				// ���������գ�����ָ���ָ
		Thrt->lchild = Thrt;
	} else{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);		// ���������������������
		pre->rchild = Thrt;
		pre->RTag = Thread;	// ���һ�����������
		Thrt->rchild = pre;
	}
	return OK;
}// InOrderThreading

void InThreading(BiThrTree p){
	// ���������������������
	if (p){
		InThreading(p->lchild);	// ������������
		if (!p->lchild){
			p->LTag = Thread;	// ǰ������
			p->lchild = pre;
		}
		if (!pre->rchild){
			pre->RTag = Thread;	// �������
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}// InThreading