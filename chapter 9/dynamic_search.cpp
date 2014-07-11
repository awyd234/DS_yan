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