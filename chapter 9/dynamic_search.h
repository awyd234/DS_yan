#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

#define LH	+1		// 左高
#define EH	0		// 等高
#define RH	-1		// 右高

//----- 二叉排序树的类型定义 -----
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