#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

BiTree SearchBST(BiTree T, KeyType key){
	// �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ�
	// �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
	if ((!T) || EQ(key, T->data.key)){		// ���ҽ���
		return T;
	} else if LT(key, T->data.key){	
		return(SearchBST(T->lchild, key));	// ���������м�������
	} else{
		return(SearchBST(T->rchild, key));	// ���������м�������
	}
}// BiTree SearchBST

Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p){
	// �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������ҳɹ���
	// ��ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���Ϸ��ʵ����
	// һ����㲢����FALSE��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
	if (!T){									// ���Ҳ��ɹ�
		p = f;
		return	FALSE;
	} else if EQ(key,T->data.key){				// ���ҳɹ�
		p = T;
		return TRUE;
	} else if LT(key, T->data.key){
		return SearchBST(T->lchild, key, T, p);	// ���������м�������
	} else{
		return SearchBST(T->rchild, key, T, p);	// ���������м�������
	}
}// Status SearchBST

Status InsertBST(BiTree &T, ElemType e){
	// ������������T�в����ڹؼ��ֹؼ��ֵ���e.key������Ԫ��ʱ������e������TRUE
	// ���򷵻�FALSE
	BiTree p;
	BiTNode *s;
	if (!SearchBST(T, e.key, NULL, p)){			// ���Ҳ��ɹ�
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p){
			T = s;								// ������*sΪ�µĸ����
		} else if LT(e.key, p->data.key){
			p->lchild = s;						// ������*sΪ����
		} else{
			p->rchild = s;						// ������*sΪ�Һ���
		}
		return TRUE;
	} else{
		return FALSE;							// �������йؼ�����ͬ�Ľ�㣬���ٲ���
	}
}// InsertBST

Status DeleteBST(BiTree &T, KeyType key){
	// ������������T�д��ڹؼ���Ϊkey������Ԫ�أ���ɾ��������Ԫ�ؽ��
	// ������TRUE�����򷵻�FALSE
	if (!T){									// �����ڹؼ��ֵ���key������Ԫ��
		return FALSE;
	} else{
		if (EQ(key, T->data.key)){				// �ҵ��ؼ��ֵ���key������Ԫ��
			return Delete(T);
		} else if (LT(key, T->data.key)){
			return DeleteBST(T->lchild, key);
		} else{
			return DeleteBST(T->rchild, key);
		}
	}
}// DeleteBST

Status Delete(BiTree &p){
	// �Ӷ�����������ɾ�����p�����ؽ��������������
	BiTree s, q;
	if (!p->rchild){							// ������Ϊ����ֻ���ؽ�����������
		q = p;
		p = p->lchild;
		free(q);
	} else if (!p->lchild){						// ֻ���ؽ�����������
		q = p;
		p = p->rchild;
		free(q);
	} else{										// ��������������
		q = p;
		s = p->lchild;
		while (s->rchild){
			q = s;
			s = s->rchild;						// ת��Ȼ�����ҵ���ͷ
		}
		p->data = s->data;						// sָ��ɾ���ġ�ǰ����
		if (q != p){
			q->rchild = s->lchild;				// �ؽ�*q��������
		} else{
			q->lchild = s->lchild;				// �ؽ�*q��������
		}
		delete s;
	}
	return TRUE;
}// Delete

void R_Rotate(BSTree &p){
	// ����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת
	// ����֮ǰ���������ĸ����
	BSTree lc;
	lc = p->lchild;								// lcָ���*p�������������
	p->lchild = lc->rchild;						// lc���������ҽ�Ϊ*p��������
	lc->rchild = p;
	p = lc;										// pָ���µĸ����
}// R_Rotate

void L_Rotate(BSTree &p){
	// ����*pΪ���Ķ�����������������������֮��pָ���µ�������㣬����ת
	// ����֮ǰ���������ĸ����
	BSTree rc;
	rc = p->rchild;								// rcָ���*p�������������
	p->rchild = rc->lchild;						// lc���������ҽ�Ϊ*p��������
	rc->lchild = p;
	p = rc;										// pָ���µĸ����
}// L_Rotate

Status InsertAVL(BSTree &T, ElemType e, Boolean &taller){
	// ����ƽ��Ķ���������T�в����ں�e��ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��
	// Ϊe���½�㣬������TRUE,���򷵻�FALSE����������ʹ������������ȥƽ�⣬
	// ����ƽ����ת������������taller��ӦT�������
	if (!T){									// �����½�㣬�������ߡ�����tallerΪTRUE
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = TRUE;
	} else{
		if (EQ(e.key, T->data.key)){			// �����Ѵ��ں�e����ͬ�ؼ��ֵĽ��
			taller = FALSE;						// ���ٲ���
			return FALSE;
		}
		if (LT(e.key, T->data.key)){			// Ӧ������*T���������н�������
			if (!InsertAVL(T->lchild, e, taller)){		// δ����
				return	0;
			}
			if (taller){						// �Ѳ��뵽*T�����������������������ߡ�
				switch (T->bf) {				// ���*T��ƽ���
				case LH:						// ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					LeftBalance(T);
					taller = FALSE;
					break;
				case EH:					// ԭ�����������ȸߣ��������������߶�ʹ������
					T->bf = LH;
					taller = TRUE;
					break;
				case RH:						// ԭ�����������������ߣ������������ȸ�
					T->bf = EH;
					taller = FALSE;
					break;
				}// switch
			}
		} else{									// Ӧ������*T���������н�������
			if (!InsertAVL(T->rchild, e, taller)){		// δ����
				return 0;
			}
			if (taller){						// �Ѳ��뵽*T��������������������
				switch (T->bf) {				// ���*T��ƽ���
				case LH:					// ԭ�����������������ߣ��������������ȸ�
					T->bf = EH;
					taller = FALSE;
					break;
				case EH:				// ԭ�����������ȸߣ��������������߶�ʹ������
					T->bf = RH;
					taller = TRUE;
					break;
				case RH:					// ԭ�����������������ߣ���Ҫ����ƽ�⴦��
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
	// ���Ը�T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ��
	// �µĸ����
	BSTree lc, rd;
	lc = T->lchild;					// lcָ��*T�������������
	switch (lc->bf) {				// ���*T����������ƽ��ȣ�������Ӧƽ�⴦��
	case LH:					// �½�������*T�����ӵ��������ϣ�Ҫ������������
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:					// �½�������*T�����ӵ��������ϣ�Ҫ��˫������
		rd = lc->rchild;		// rdָ��*T�����ӵ���������
		switch (rd->bf) {		// �޸�*T�������ӵ�ƽ������
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
		L_Rotate(T->lchild);	// ��*T��������������ƽ�⴦��
		R_Rotate(T);			// ��*T������ƽ�⴦��
	}// switch(lc->bf)
}// LeftBalance

void RightBalance(BSTree &T){
	// ���Ը�T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ��
	// �µĸ����
	BSTree rc, ld;
	rc = T->rchild;					// lcָ��*T�������������
	switch (rc->bf) {				// ���*T����������ƽ��ȣ�������Ӧƽ�⴦��
	case RH:						// �½�������*T���Һ��ӵ��������ϣ�Ҫ������������
		T->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:					// �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������
		ld = rc->rchild;		// ldָ��*T���Һ��ӵ���������
		switch (ld->bf) {		// �޸�*T�����Һ��ӵ�ƽ������
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
		R_Rotate(T->rchild);	// ��*T��������������ƽ�⴦��
		L_Rotate(T);			// ��*T������ƽ�⴦��
	}// switch(rc->bf)
}// RightBalance

Result SearchBTree(BTree T, KeyType K){
	// ��m��B-��T�ϲ��ҹؼ���K�����ؽ����pt,i,tag���������ҳɹ���������ֵtag=1��ָ��
	// pt��ָ����е�i���ؼ��ֵ���K����������ֵtag=0������K�Ĺؼ���Ӧ������ָ��pt��ָ
	// ����е�i�͵�i+1���ؼ���֮��
	int i;
	BTree p, q;
	bool found;
	p = T;						// ��ʼ����pָ������㣬qָ��p��˫��
	q = NULL;
	found = FALSE;
	i = 0;
	while (p&&!found){
		i = Search(p, K);		// ��p->key[1..keynum]�в���
								// iʹ�ã�p->key[i] <= K < p->key[i+1]
		if (i > 0 && p->key[i] == K){
			found = TRUE;		// �ҵ�����ؼ���
		} else{
			q = p;
			p = p->ptr[i];
		}
	}// while
	if (found){					//���ҳɹ�
		return{ p, i, 1 };
	} else{						//���Ҳ��ɹ�������K�Ĳ���λ����Ϣ 
		return{ q, i, 0 };
	}
}// SearchBTree

int Search(BTree T, KeyType K){
	// ��p->key[1..keynum]�в���iʹ�ã�T->key[i] <= K < T->key[i+1]
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
	// ��m��B-��T�ϲ���ؼ���K
	// ���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT��Ϊm��B-��
	int s;
	KeyType x;
	Result res;
	BTree ap;						// ���ѳ��Ľ��
	BTree q;
	int i;
	bool finished;
	x = K;
	res = SearchBTree(T, K);		// ��Ҫ�����λ��
	q = res.p;
	i = res.i;
	ap = NULL;
	finished = FALSE;
	if (res.tag) {					// �Ѿ����ڣ��������
		return 0;
	}
	while (q&&!finished){
		Insert(q, i, x, ap);		// ��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
		if (q->keynum < m) {
			finished = TRUE;		// �������
		} else {					// ���ѽ��*q
			s = (m % 2 == 0) ? m / 2 : (m / 2 + 1);
			split(q, s, ap);		// ��q->key[s+1..m],q->ptr[s..m],��q->recptr[s+1..m]�����½��ap
			x = q->key[s];			
			q = q->parent;
			if (q) {
				i = Search(q, x);	// ��˫�׽��*q�в���x�Ĳ���λ��
			}
		}// else
	}// while
	if (!finished) {			// T�ǿ���������q��ֵΪNULL�����߸�����ѷ���Ϊ���*q��*qp
		NewRoot(T, q, x, ap);		// ���ɺ���Ϣ��T,x,ap�����µĸ����*T��ԭT��apΪ����ָ��
	}
	return OK;
}// InsertBTree

Status Insert(BTree q, int i, KeyType x, BTree ap) {
	// ��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
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
	// ��q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]�����½��ap
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
	// ���ɺ���Ϣ��T,x,ap�����µĸ����*T��ԭT��apΪ����ָ��
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
	// �����ļ�filename����B-��T
	FILE *fp;
	KeyType e;
	fp = fopen(filename, "r");							// ���ļ���ֻ��
	if (!fp) {
		printf("Fail to open the file: %s!", filename);
		return ERROR;
	}
	while (fscanf(fp, "%d", &e)!=EOF) {					// ���ζ�ȡ�ļ�����e��ֱ��EOF
		InsertBTree(T, e);								// ��e������T��
	}
	fclose(fp);
	return OK;
}// CreateBTree

void DisplayBTree(BTree T) {
	// �����ӡT
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
