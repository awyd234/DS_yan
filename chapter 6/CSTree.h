#ifndef _CSTREE_H_
#define _CSTREE_H_

//----- ���Ķ����������� - �ֵܣ��洢��ʾ -----

typedef struct CSNode{
	TElemType		data;
	struct CSNode	*firstchild, *nextsibling;
}CSNode, *CSTree;

#endif