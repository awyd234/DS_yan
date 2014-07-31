#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e) {
	// 静态链表L的r域中记录已按(key[0],..,key[i-1])有序。
	// 本算法按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
	// f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录
	int j, p;
	for (j = 0; j < RADIX; j++) {			// 各子表初始化为空表
		f[j] = 0;
	}
	for (p = r[0].next; p; p = r[p].next) {
		j = ord(r[p].keys[i]);
		if (!f[j]) {
			f[j] = p;
		} else {
			r[e[j]].next = p;
		}
		e[j] = p;							// 将p所指结点插入到底j个子表中
	}
}// Distribute

int ord(ElemType K) {
	// 将记录中关键字映射到[0..RADIX-1]
	return K;
}// ord

void Collect(SLCell r[], int i, ArrType f, ArrType e) {
	// 本算法按keys[i]自小到大地将f[0..RADIX-1]所指各子表依次链接成一个链表,
	// e[0..RAD-1]为各表的尾指针
	int t, j;
	for (j = 0; !f[j]; j = succ(f, j)) {		// 找到第一个非空子表
		;
	}
	r[0].next = f[j];							// r[0].next指向第一个非空子表中第一个结点
	t = e[j];
	while (j < RADIX) {
		for (j = succ(f, j); j < RADIX - 1 && !f[j]; j = succ(f, j)) {	// 找下一个非空子表
			;
		}
		if (f[j] && j < RADIX) {
			r[t].next = f[j];
			t = e[j];						// 链接两个非空子表
		}
	}
	r[t].next = 0;							// t指向最后一个非空子表中的最后一个结点
}// Collect

int succ(ArrType f, int j) {
	// 后继函数
	return ++j;
}// succ

void RadixSort(SLList &L) {
	// L是采用静态链表表示的顺序表
	// 对L作基数排序，使得L成为关键字自小到大的有序静态链表，L.r[0]为头结点
	int i;
	ArrType e, f;
	for (i = 0; i < L.recnum; i++) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (i = 0; i < L.keynum; i++) {	// 按最低为优先依次对各关键字进行分配和收集
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}// RadixSort

Status CreateRadixSort(SLList &L, char *filename) {
	// CreateRadixSort
	FILE *fp;
	KeysType e;
	L.keynum = 3;
	L.recnum = 0;
	fp = fopen(filename, "r");
	while (fscanf(fp, "%d", &e) != EOF) {
		L.recnum++;
		L.r[L.recnum].keys[2] = e / 100;
		L.r[L.recnum].keys[1] = (e % 100) / 10;
		L.r[L.recnum].keys[0] = e % 10;
	}
	fclose(fp);
	return OK;
}// CreateRadixSort
