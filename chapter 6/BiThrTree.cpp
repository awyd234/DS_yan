#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status CreateBiThrTree(BiThrTree &T){
	// 按先序次序输入二叉线索树中结点的值（一个字符），空格字符表示空树
	// 构造二叉链表表示的线索二叉树T
	TElemType ch;
	#if CHAR				// 参考课本资料给代码
		scanf("%c", &ch);
	#else
		scanf("%d", &ch);
	#endif
	if (ch == ' '){
		T = NULL;
	} else{
		if (!(T = (BiThrNode *)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data = ch;
		CreateBiThrTree(T->lchild);	// 构造左子树
		if (T->lchild)				// 有左孩子
			T->LTag = Link;
		CreateBiThrTree(T->rchild);	// 构造右子树
		if (T->rchild)				// 有右孩子
			T->RTag = Link;
	}
	return OK;
}// CreateBiThrTree

Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e)){
	// T指向头结点，头结点的左链lchild指向根结点
	// 中序遍历二叉线索树T的非递归算法，对每个数据元素调用函数Visit
	BiThrTree p = T->lchild;	// p指向根结点
	while (p != T){				// 空树或遍历结束时，p==T
		while (p->LTag == Link) p = p->lchild;
		if (!Visit(p->data)) return ERROR;		// 访问其左子树为空的结点
		while (p->RTag == Thread&&p->rchild != T){
			p = p->rchild;		// 访问后继结点
			Visit(p->data);	
		}
		p = p->rchild;
	}
	return OK;
}// InOrderTraverse_Thr

BiThrTree pre;
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	// 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	Thrt->LTag = Link;		// 建头结点
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;	// 右指针回指
	if (!T){				// 若二叉树空，则左指针回指
		Thrt->lchild = Thrt;
	} else{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);		// 中序遍历进行中序线索化
		pre->rchild = Thrt;
		pre->RTag = Thread;	// 最后一个结点线索化
		Thrt->rchild = pre;
	}
	return OK;
}// InOrderThreading

void InThreading(BiThrTree p){
	// 中序遍历进行中序线索化
	if (p){
		InThreading(p->lchild);	// 左子树线索化
		if (!p->lchild){
			p->LTag = Thread;	// 前驱线索
			p->lchild = pre;
		}
		if (!pre->rchild){
			pre->RTag = Thread;	// 后继线索
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}// InThreading