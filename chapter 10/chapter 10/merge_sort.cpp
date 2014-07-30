#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

void Merge(int SR[], int TR[], int i, int m, int n) {
	// �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
	int j, k;
	for (j = m + 1, k = i; i <= m&&j <= n; ++k) {
		if (LQ(SR[i], SR[j])) {
			TR[k] = SR[i++];
		} else {
			TR[k] = SR[j++];
		}
	}
	if (i <= m) {
		for (j = i; j <= m; j++) {
			TR[k++] = SR[j];
		}
	}
	if (j <= n) {
		for (i = j; i <= n; i++) {
			TR[k++] = SR[i];
		}
	}
}// Merge

void MSort(int SR[], int TR1[], int s, int t) {
	// ��SR[s..t]�鲢����ΪTR1[s..t]
	int m;
	int TR2[100+10];
	if (s == t) {
		TR1[s] = SR[s];
	} else {
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}// MSort

void MergeSort(SqList &L) {
	// ��˳���L���鲢����
	MSort(L.elem, L.elem, 1, L.length);
}// MergeSort