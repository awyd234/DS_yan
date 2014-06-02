//----- �������Ķ��������洢��ʾ -----

#ifndef _BITHRTREE_H_
#define _BITHRTREE_H_

#define CHAR 1

typedef enum PointerTag{Link, Thread};		// Link==0��ָ�룬Thread������
typedef struct BiThrNode{
	TElemType			data;
	struct BiThrNode	*lchild, *rchild;	// ���Һ���ָ��
	PointerTag			LTag, RTag;			// ���ұ�־
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree &T);
Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e));
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrTree p);

#endif