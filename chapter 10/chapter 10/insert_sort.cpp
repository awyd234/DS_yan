#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status CreateSqList(SqList &L, char *filename) {
	// �����ļ�filename����L
	ElemType e;
	InitList_Sq(L);
	FILE *fp;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Fail to open the file: %s!\n", filename);
		return ERROR;
	}
	while (fscanf(fp, "%d", &e) != EOF) {
		ListInsert_Sq(L, 2, e);
	}
	fclose(fp);
	return OK;
}// CreateSqList

void InsertSort(SqList &L) {
	// ��˳���L��ֱ�Ӳ�������
	int i, j;
	for (i = 2; i <= L.length; i++) {
		if (LT(L.elem[i], L.elem[i - 1])) {		// ��<��,��Ҫ��L.elem[i]���������ӱ�
			L.elem[0] = L.elem[i];				// ����Ϊ�ڱ�
			L.elem[i] = L.elem[i - 1];
			for (j = i - 2; LT(L.elem[0], L.elem[j]); j--) {
				L.elem[j + 1] = L.elem[j];		// ��¼����
			}
			L.elem[j + 1] = L.elem[0];			// ���뵽��ȷλ��
		}// if
	}
}// InsertSort

void BInsertSort(SqList &L) {
	// ��˳���L���۰��������
	int i, j, m, low, high;
	for (i = 2; i <= L.length; i++) {
		L.elem[0] = L.elem[i];			// ��L.elme[i]�ݴ浽L.elem[0]
		low = 1; 
		high = i - 1;
		while (low <= high) {
			m = (low + high) / 2;		// �۰�
			if (LT(L.elem[0], L.elem[m])) {
				high = m - 1;			// �����ڵͰ���
			} else {
				low = m + 1;			// �����ڸ߰���
			}
		}// while
		for (j = i - 1; j >= high + 1; --j) {
			L.elem[j + 1] = L.elem[j];	// ��¼����
		}
		L.elem[high + 1] = L.elem[0];	// ����
	}
}// BInsertSort

void TwoInsertSort(SqList &L) {
	// ��L����2·����
	int i, j;
	int first, final;
	ElemType *d;
	d = (ElemType *)malloc(L.length*sizeof(ElemType));
	first = 0;
	final = 0;
	if (L.length > 0) {
		d[1] = L.elem[1];
		final = 1;
		first = 1;
	}
	for (i = 2; i <= L.length; i++) {
		if (LT(L.elem[i], L.elem[1])) {	// ���뵽ǰ�벿��
			if (first == 1) {
				first = L.length;
				d[first] = L.elem[i];
			} else {
				for (j = first; LT(d[j], L.elem[i]); j++) {
					d[j - 1] = d[j];
				}
				--first;
				d[j - 1] = L.elem[i];
			}
		} else {						// ���뵽��벿��
			for (j = final; L.elem[i] < d[j]; j--) {
				d[j+1] = d[j];
			}
			final++;
			d[j + 1] = L.elem[i];
		}
	}
	if (!first) {
		for (i = 2; i <= L.length; i++) {
			L.elem[i] = d[i];
		}
	} else {
		for (i = first, j = 1; i <= L.length; i++, j++) {
			L.elem[j] = d[i];
		}
		for (i = 1; i <= final; i++, j++) {
			L.elem[j] = d[i];
		}
	}
}// TwoInsertSort

void TableInsertSort(SLinkListType &S) {
	// ��L���б��������
	int i, p, j;
	S.r[0].key = INT_MAX;
	if (S.length > 0) {
		S.r[0].next = 1;
		S.r[1].next = 0;
	}
	for (i = 2; i <= S.length; i++) {
		p = 0;
		for (j = S.r[0].next; S.r[i].key > S.r[j].key&&j > 0;
			 p = j, j = S.r[j].next) {
			;
		}
		S.r[i].next = j;
		S.r[p].next = i;
	}
}// TableInsertSort

Status CreateLinkList(SLinkListType &SL, char *filename) {
	// �����ļ�filename������̬����SL
	FILE *fp;
	int i = 1, key;
	SL.length = 0;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Fail to open the file: %s!\n", filename);
		return ERROR;
	}
	while (fscanf(fp, "%d", &key) != EOF) {
		SL.r[i++].key = key;
		SL.length++;
	}
	fclose(fp);
	return OK;
}// CreateLinkList
