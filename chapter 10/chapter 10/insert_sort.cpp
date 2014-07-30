#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status CreateSqList(SqList &L, char *filename) {
	// 根据文件filename创建L
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
	// 对顺序表L做直接插入排序
	int i, j;
	for (i = 2; i <= L.length; i++) {
		if (LT(L.elem[i], L.elem[i - 1])) {		// “<”,需要将L.elem[i]插入有序子表
			L.elem[0] = L.elem[i];				// 复制为哨兵
			L.elem[i] = L.elem[i - 1];
			for (j = i - 2; LT(L.elem[0], L.elem[j]); j--) {
				L.elem[j + 1] = L.elem[j];		// 记录后移
			}
			L.elem[j + 1] = L.elem[0];			// 插入到正确位置
		}// if
	}
}// InsertSort

void BInsertSort(SqList &L) {
	// 对顺序表L作折半插入排序
	int i, j, m, low, high;
	for (i = 2; i <= L.length; i++) {
		L.elem[0] = L.elem[i];			// 将L.elme[i]暂存到L.elem[0]
		low = 1; 
		high = i - 1;
		while (low <= high) {
			m = (low + high) / 2;		// 折半
			if (LT(L.elem[0], L.elem[m])) {
				high = m - 1;			// 插入在低半区
			} else {
				low = m + 1;			// 插入在高半区
			}
		}// while
		for (j = i - 1; j >= high + 1; --j) {
			L.elem[j + 1] = L.elem[j];	// 记录后移
		}
		L.elem[high + 1] = L.elem[0];	// 插入
	}
}// BInsertSort

void TwoInsertSort(SqList &L) {
	// 对L进行2路排序
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
		if (LT(L.elem[i], L.elem[1])) {	// 插入到前半部分
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
		} else {						// 插入到后半部分
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
	// 对L进行表插入排序
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
	// 根据文件filename创建静态链表SL
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
