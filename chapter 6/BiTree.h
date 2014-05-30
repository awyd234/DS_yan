#ifndef _BITREE_H_
#define _BITREE_H_

//----- 二叉树的二叉链表存储表示 -----

typedef char TElemType;

typedef struct BiTNode{
	TElemType		data;
	struct BiTNode	*lchild, *rchild;	// 左右孩子指针
	Status			FirstVisted;
}BiTNode, *BiTree;

typedef BiTree QElemType;

Status CreateBiTree(BiTree &T);
Status PreOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e));
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse2(BiTree T, Status(*Visit)(TElemType e));
Status InOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e));
Status PostOrderTraverse_Recur(BiTree T, Status(*Visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e));
Status PrintElement(TElemType e);

#endif