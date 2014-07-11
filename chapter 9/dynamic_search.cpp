#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

BiTree SearchBST(BiTree T, KeyType key){
	// 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，
	// 若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
	if ((!T) || EQ(key, T->data.key)){		// 查找结束
		return T;
	} else if LT(key, T->data.key){	
		return(SearchBST(T->lchild, key));	// 在左子树中继续查找
	} else{
		return(SearchBST(T->rchild, key));	// 在右子树中继续查找
	}
}// BiTree SearchBST

Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p){
	// 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找成功，
	// 则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上访问的最后
	// 一个结点并返回FALSE，指针f指向T的双亲，其初始调用值为NULL
	if (!T){									// 查找不成功
		p = f;
		return	FALSE;
	} else if EQ(key,T->data.key){				// 查找成功
		p = T;
		return TRUE;
	} else if LT(key, T->data.key){
		return SearchBST(T->lchild, key, T, p);	// 在左子树中继续查找
	} else{
		return SearchBST(T->rchild, key, T, p);	// 在右子树中继续查找
	}
}// Status SearchBST

Status InsertBST(BiTree &T, ElemType e){
	// 当二叉排序树T中不存在关键字关键字等于e.key的数据元素时，插入e并返回TRUE
	// 否则返回FALSE
	BiTree p;
	BiTNode *s;
	if (!SearchBST(T, e.key, NULL, p)){			// 查找不成功
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p){
			T = s;								// 被插结点*s为新的根结点
		} else if LT(e.key, p->data.key){
			p->lchild = s;						// 被插结点*s为左孩子
		} else{
			p->rchild = s;						// 被插结点*s为右孩子
		}
		return TRUE;
	} else{
		return FALSE;							// 树中已有关键字相同的结点，不再插入
	}
}// InsertBST

Status DeleteBST(BiTree &T, KeyType key){
	// 若二叉排序树T中存在关键字为key的数据元素，则删除该数据元素结点
	// 并返回TRUE，否则返回FALSE
	if (!T){									// 不存在关键字等于key的数据元素
		return FALSE;
	} else{
		if (EQ(key, T->data.key)){				// 找到关键字等于key的数据元素
			return Delete(T);
		} else if (LT(key, T->data.key)){
			return DeleteBST(T->lchild, key);
		} else{
			return DeleteBST(T->rchild, key);
		}
	}
}// DeleteBST

Status Delete(BiTree &p){
	// 从二叉排序树中删除结点p，并重接它的左或右子树
	BiTree s, q;
	if (!p->rchild){							// 右子树为空着只需重接它的左子树
		q = p;
		p = p->lchild;
		free(q);
	} else if (!p->lchild){						// 只需重接它的右子树
		q = p;
		p = p->rchild;
		free(q);
	} else{										// 左右子树均不空
		q = p;
		s = p->lchild;
		while (s->rchild){
			q = s;
			s = s->rchild;						// 转左，然后向右到尽头
		}
		p->data = s->data;						// s指向被删结点的“前驱”
		if (q != p){
			q->rchild = s->lchild;				// 重接*q的右子树
		} else{
			q->lchild = s->lchild;				// 重接*q的左子树
		}
		delete s;
	}
	return TRUE;
}// Delete

void R_Rotate(BSTree &p){
	// 对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转
	// 处理之前的左子树的根结点
	BSTree lc;
	lc = p->lchild;								// lc指向的*p的左子树根结点
	p->lchild = lc->rchild;						// lc的右子树挂接为*p的左子树
	lc->rchild = p;
	p = lc;										// p指向新的根结点
}// R_Rotate

void L_Rotate(BSTree &p){
	// 对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转
	// 处理之前的右子树的根结点
	BSTree rc;
	rc = p->rchild;								// rc指向的*p的右子树根结点
	p->rchild = rc->lchild;						// lc的左子树挂接为*p的右子树
	rc->lchild = p;
	p = rc;										// p指向新的根结点
}// L_Rotate

Status InsertAVL(BSTree &T, ElemType e, Boolean &taller){
	// 若在平衡的二叉排序树T中不存在和e相同关键字的结点，则插入一个数据元素
	// 为e的新结点，并返回TRUE,否则返回FALSE。若因插入而使二叉排序树数去平衡，
	// 则作平衡旋转处理，布尔变量taller反应T长高与否
	if (!T){									// 插入新结点，树“长高”，置taller为TRUE
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = TRUE;
	} else{
		if (EQ(e.key, T->data.key)){			// 树中已存在和e有相同关键字的结点
			taller = FALSE;						// 则不再插入
			return FALSE;
		}
		if (LT(e.key, T->data.key)){			// 应继续在*T的左子树中进行搜索
			if (!InsertAVL(T->lchild, e, taller)){		// 未插入
				return	0;
			}
			if (taller){						// 已插入到*T的左子树中且左子树“长高”
				switch (T->bf) {				// 检查*T的平衡度
				case LH:						// 原本左子树比右子树高，需要作做平衡处理
					LeftBalance(T);
					taller = FALSE;
					break;
				case EH:					// 原本左、右子树等高，现因左子树增高而使树增高
					T->bf = LH;
					taller = TRUE;
					break;
				case RH:						// 原本右子树比左子树高，现左、右子树等高
					T->bf = EH;
					taller = FALSE;
					break;
				}// switch
			}
		} else{									// 应继续在*T的右子树中进行搜索
			if (!InsertAVL(T->rchild, e, taller)){		// 未插入
				return 0;
			}
			if (taller){						// 已插入到*T的右子树且右子树长高
				switch (T->bf) {				// 检查*T的平衡度
				case LH:					// 原本左子树比右子树高，现在左、右子树等高
					T->bf = EH;
					taller = FALSE;
					break;
				case EH:				// 原本左、右子树等高，现因右子树增高而使树增高
					T->bf = RH;
					taller = TRUE;
					break;
				case RH:					// 原本右子树比左子树高，需要作右平衡处理
					RightBalance(T);
					taller = FALSE;
					break;
				}
			}
		}// else
	}// else
	return TRUE;
}// InsertAVL

void LeftBalance(BSTree &T){
	// 对以根T所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针T指向
	// 新的根结点
	BSTree lc, rd;
	lc = T->lchild;					// lc指向*T的左子树根结点
	switch (lc->bf) {				// 检查*T的左子树的平衡度，并作相应平衡处理
	case LH:					// 新结点插入在*T的左孩子的左子树上，要作单右旋处理
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:					// 新结点插入在*T的左孩子的右子树上，要作双旋处理
		rd = lc->rchild;		// rd指向*T的左孩子的右子树根
		switch (rd->bf) {		// 修改*T及其左孩子的平衡因子
		case LH:
			T->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			T->bf = lc->bf = EH;
			break;
		case RH:
			T->bf = EH;
			lc->bf = LH;
		}// switch(rd->bf)
		rd->bf = EH;
		L_Rotate(T->lchild);	// 对*T的左子树作左旋平衡处理
		R_Rotate(T);			// 对*T作右旋平衡处理
	}// switch(lc->bf)
}// LeftBalance

void RightBalance(BSTree &T){
	// 对以根T所指结点为根的二叉树作右平衡旋转处理，本算法结束时，指针T指向
	// 新的根结点
	BSTree rc, ld;
	rc = T->rchild;					// lc指向*T的右子树根结点
	switch (rc->bf) {				// 检查*T的右子树的平衡度，并作相应平衡处理
	case RH:						// 新结点插入在*T的右孩子的右子树上，要作单左旋处理
		T->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:					// 新结点插入在*T的右孩子的左子树上，要作双旋处理
		ld = rc->rchild;		// ld指向*T的右孩子的左子树根
		switch (ld->bf) {		// 修改*T及其右孩子的平衡因子
		case LH:
			T->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			T->bf = rc->bf = EH;
			break;
		case RH:
			T->bf = LH;
			rc->bf = EH;
		}// switch(ld->bf)
		ld->bf = EH;
		R_Rotate(T->rchild);	// 对*T的右子树作右旋平衡处理
		L_Rotate(T);			// 对*T作左旋平衡处理
	}// switch(rc->bf)
}// RightBalance