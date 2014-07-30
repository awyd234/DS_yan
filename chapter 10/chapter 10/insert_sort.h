#ifndef _INSERT_SORT_H_
#define _INSERT_SORT_H_

#include "MyHeader.h"

//----- ��̬����Ĵ洢��ʾ -----
#define SIZE 100		// ��̬��������

typedef struct {
	int key;			// �ؼ���
	int next;			// ָ����
}SLNode;				// ��������

typedef struct {
	SLNode	r[SIZE];	// 0�ŵ�ԪΪ��ͷ���
	int length;			// ����ǰ����
}SLinkListType;			// ��̬��������

Status CreateSqList(SqList &L, char *filename);
void InsertSort(SqList &L);
void BInsertSort(SqList &L);
void TwoInsertSort(SqList &L);
void TableInsertSort(SLinkListType &S);
Status CreateLinkList(SLinkListType &SL, char *filename);

#endif