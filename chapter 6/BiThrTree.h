//----- 二叉树的二叉线索存储表示 -----

#ifndef _BITHRTREE_H_
#define _BITHRTREE_H_

#define CHAR 1

typedef enum PointerTag{Link, Thread};		// Link==0：指针，Thread：线索
typedef struct BiThrNode{
	TElemType			data;
	struct BiThrNode	*lchild, *rchild;	// 左右孩子指针
	PointerTag			LTag, RTag;			// 左右标志
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);

#endif