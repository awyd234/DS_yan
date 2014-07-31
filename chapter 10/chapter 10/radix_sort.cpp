#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e) {
	// ��̬����L��r���м�¼�Ѱ�(key[0],..,key[i-1])����
	// ���㷨����i���ؼ���keys[i]����RADIX���ӱ�ʹͬһ�ӱ��м�¼��keys[i]��ͬ
	// f[0..RADIX-1]��e[0..RADIX-1]�ֱ�ָ����ӱ��е�һ�������һ����¼
	int j, p;
	for (j = 0; j < RADIX; j++) {			// ���ӱ��ʼ��Ϊ�ձ�
		f[j] = 0;
	}
	for (p = r[0].next; p; p = r[p].next) {
		j = ord(r[p].keys[i]);
		if (!f[j]) {
			f[j] = p;
		} else {
			r[e[j]].next = p;
		}
		e[j] = p;							// ��p��ָ�����뵽��j���ӱ���
	}
}// Distribute

int ord(ElemType K) {
	// ����¼�йؼ���ӳ�䵽[0..RADIX-1]
	return K;
}// ord

void Collect(SLCell r[], int i, ArrType f, ArrType e) {
	// ���㷨��keys[i]��С����ؽ�f[0..RADIX-1]��ָ���ӱ��������ӳ�һ������,
	// e[0..RAD-1]Ϊ�����βָ��
	int t, j;
	for (j = 0; !f[j]; j = succ(f, j)) {		// �ҵ���һ���ǿ��ӱ�
		;
	}
	r[0].next = f[j];							// r[0].nextָ���һ���ǿ��ӱ��е�һ�����
	t = e[j];
	while (j < RADIX) {
		for (j = succ(f, j); j < RADIX - 1 && !f[j]; j = succ(f, j)) {	// ����һ���ǿ��ӱ�
			;
		}
		if (f[j] && j < RADIX) {
			r[t].next = f[j];
			t = e[j];						// ���������ǿ��ӱ�
		}
	}
	r[t].next = 0;							// tָ�����һ���ǿ��ӱ��е����һ�����
}// Collect

int succ(ArrType f, int j) {
	// ��̺���
	return ++j;
}// succ

void RadixSort(SLList &L) {
	// L�ǲ��þ�̬�����ʾ��˳���
	// ��L����������ʹ��L��Ϊ�ؼ�����С���������̬����L.r[0]Ϊͷ���
	int i;
	ArrType e, f;
	for (i = 0; i < L.recnum; i++) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (i = 0; i < L.keynum; i++) {	// �����Ϊ�������ζԸ��ؼ��ֽ��з�����ռ�
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
