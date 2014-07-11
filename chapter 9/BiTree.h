#ifndef _BITREE_H_
#define _BITREE_H_

#include "MyHeader.h"

//----- �������Ķ�������洢��ʾ -----

typedef ElemType TElemType;

typedef struct BiTNode{
	TElemType		data;
	int bf;								// ����ƽ������
	struct BiTNode	*lchild, *rchild;	// ���Һ���ָ��
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