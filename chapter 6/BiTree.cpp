#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

Status CreateBiTree(BiTree &T){
	// 按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树
	// 构造二叉链表表示的二叉树T
	char ch;
	scanf("%c",&ch);
	//getchar();		// 读取回车
	if (ch == ' '){
		T = NULL;
	} else{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;				// 生成根结点
		CreateBiTree(T->lchild);	// 构造左子树
		CreateBiTree(T->rchild);	// 构造右子树
	}
	return OK;
}// CreateBiTree

Status PreOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e)){
	// 采用二叉树链表存储结构，Visit是对数据元素操作的应用函数
	// 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
	if (T){
		if (Visit(T->data))
			if (PreOrderTraverse_Recur(T->lchild, Visit))
				if (PreOrderTraverse_Recur(T->rchild, Visit))
					return OK;
		return ERROR;
	}else return OK;
}// PreOrderTraverse_Recur

Status InOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e)){
	// 采用二叉树链表存储结构，Visit是对数据元素操作的应用函数
	// 中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
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
	// 采用二叉树链表存储结构，Visit是对数据元素操作的应用函数
	// 中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit
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
	// 采用二叉树链表存储结构，Visit是对数据元素操作的应用函数
	// 中序遍历二叉树T的非递归算法2，对每个数据元素调用函数Visit
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
	// 采用二叉树链表存储结构，Visit是对数据元素操作的应用函数
	// 后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
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
	// 输出元素e的值
	printf("%c" , e);
	return OK;
}// PrintElement
