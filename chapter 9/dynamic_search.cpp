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

Result SearchBTree(BTree T, KeyType K){
	// 在m阶B-树T上查找关键字K，返回结果（pt,i,tag）。若查找成功，则特征值tag=1，指针
	// pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的关键字应插入在指针pt所指
	// 结点中第i和第i+1个关键字之间
	int i;
	BTree p, q;
	bool found;
	p = T;						// 初始化，p指向待查结点，q指向p的双亲
	q = NULL;
	found = FALSE;
	i = 0;
	while (p&&!found){
		i = Search(p, K);		// 在p->key[1..keynum]中查找
								// i使得：p->key[i] <= K < p->key[i+1]
		if (i > 0 && p->key[i] == K){
			found = TRUE;		// 找到待查关键字
		} else{
			q = p;
			p = p->ptr[i];
		}
	}// while
	if (found){					//查找成功
		return{ p, i, 1 };
	} else{						//查找不成功，返回K的插入位置信息 
		return{ q, i, 0 };
	}
}// SearchBTree

int Search(BTree T, KeyType K){
	// 在p->key[1..keynum]中查找i使得：T->key[i] <= K < T->key[i+1]
	int i;
	if (K < T->key[1]){
		return 0;
	} else if (K >= T->key[T->keynum]){
		return T->keynum;
	}
	for (i = 2; i <= T->keynum; i++){
		if (K < T->key[i])
			break;
	}
	return i - 1;
}// Search

Status InsertBTree(BTree &T, KeyType K){
	// 在m阶B-树T上插入关键字K
	// 若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍为m阶B-树
	int s;
	KeyType x;
	Result res;
	BTree ap;						// 分裂出的结点
	BTree q;
	int i;
	bool finished;
	x = K;
	res = SearchBTree(T, K);		// 需要插入的位置
	q = res.p;
	i = res.i;
	ap = NULL;
	finished = FALSE;
	if (res.tag) {					// 已经存在，无需插入
		return 0;
	}
	while (q&&!finished){
		Insert(q, i, x, ap);		// 将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
		if (q->keynum < m) {
			finished = TRUE;		// 插入完成
		} else {					// 分裂结点*q
			s = (m % 2 == 0) ? m / 2 : (m / 2 + 1);
			split(q, s, ap);		// 将q->key[s+1..m],q->ptr[s..m],和q->recptr[s+1..m]移入新结点ap
			x = q->key[s];			
			q = q->parent;
			if (q) {
				i = Search(q, x);	// 在双亲结点*q中查找x的插入位置
			}
		}// else
	}// while
	if (!finished) {			// T是空树（参数q初值为NULL）或者根结点已分裂为结点*q和*qp
		NewRoot(T, q, x, ap);		// 生成含信息（T,x,ap）的新的根结点*T，原T和ap为子树指针
	}
	return OK;
}// InsertBTree

Status Insert(BTree q, int i, KeyType x, BTree ap) {
	// 将x和ap分别插入到q->key[i+1]和q->ptr[i+1]
	int j;
	for (j = q->keynum; j >= i + 1; j--) {
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i+1] = x;
	q->ptr[i+1] = ap;
	q->keynum++;
	if (ap) {
		ap->parent = q;
	}
	return OK;
}// Insert

Status split(BTree q, int s, BTree &ap){
	// 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点ap
	int i;
	q->keynum = s - 1;
	ap = (BTree)malloc(sizeof(BTNode));
	for (i = s + 1; i <= m; i++) {
		ap->key[i - s] = q->key[i];
		ap->recptr[i - s] = q->recptr[i];
	}
	for (i = s; i <= m; i++) {
		ap->ptr[i - s] = q->ptr[i];
		if (ap->ptr[i - s]) {
			ap->ptr[i - s]->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = q->parent;
	return OK;
}// split

Status NewRoot(BTree &T, BTree q, KeyType x, BTree ap){
	// 生成含信息（T,x,ap）的新的根结点*T，原T和ap为子树指针
	BTree root;
	root = (BTree)malloc(sizeof(BTNode));
	root->key[1] = x;
	root->ptr[0] = T;
	root->ptr[1] = ap;
	root->keynum = 1;
	root->parent = NULL;
	if (T) {
		T->parent = root;
	}
	if (ap) {
		ap->parent = root;
	}
	T = root;
	return OK;
}// NewRoot

Status CreateBTree(BTree &T, char *filename) {
	// 根据文件filename创建B-树T
	FILE *fp;
	KeyType e;
	fp = fopen(filename, "r");							// 打开文件，只读
	if (!fp) {
		printf("Fail to open the file: %s!", filename);
		return ERROR;
	}
	while (fscanf(fp, "%d", &e)!=EOF) {					// 依次读取文件中至e，直至EOF
		InsertBTree(T, e);								// 将e插入至T中
	}
	fclose(fp);
	return OK;
}// CreateBTree

void DisplayBTree(BTree T) {
	// 先序打印T
	int i;
	if (T) {
		for (i = 0; i <= T->keynum; i++) {
			if (i < T->keynum) {
				DisplayBTree(T->ptr[i]);
				printf("%d ", T->key[i + 1]);
			} else {
				DisplayBTree(T->ptr[i]);
			}
		}
	}
}// DisplayBTree
