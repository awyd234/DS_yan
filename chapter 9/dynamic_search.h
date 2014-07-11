#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

#define LH	+1		// ���
#define EH	0		// �ȸ�
#define RH	-1		// �Ҹ�

//----- ���������������Ͷ��� -----
typedef BiTree BSTree;
typedef BiTNode BSTNode;

BiTree SearchBST(BiTree T, KeyType key);
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p);
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);
void R_Rotate(BSTree &p);
void L_Rotata(BSTree &p);
Status InsertAVL(BSTree &T, ElemType e, Boolean &taller);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);

#endif