#ifndef _CSTREE_H_
#define _CSTREE_H_

//----- 树的二叉链表（孩子 - 兄弟）存储表示 -----

typedef struct CSNode{
	TElemType		data;
	struct CSNode	*firstchild, *nextsibling;
}CSNode, *CSTree;

#endif