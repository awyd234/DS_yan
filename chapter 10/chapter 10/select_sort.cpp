#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

void SelectSort(SqList &L) {
	// ��˳���L����ѡ������
	int i, j;
	for (i = 1; i <= L.length; i++) {	// ѡ���iС�ļ�¼����������λ
		j = SelectMinKey(L, i);			// ��L.elem[i..L.length]��ѡ����С�ļ�¼
		if (i != j) {
			Swap(L.elem[i], L.elem[j]);
		}
	}// for
}// SelectSort

int SelectMinKey(SqList L, int i) {
	// ��L.elem[i..L.length]��ѡ����С�ļ�¼
	int min = i;
	for (i++; i <= L.length; i++) {
		if (LT(L.elem[i], L.elem[min])) {
			min = i;
		}// if
	}// for
	return min;
}// SelectMinKey

void HeapAdjust(HeapType &H, int s, int m) {
	// ��֪H.elem[s..m]�м�¼�ؼ��ֳ�H.elem[s]֮�������ѵĶ��壬����������H.elem[s]
	// �Ĺؼ��֣�ʹH.elem[s..m]��Ϊ��һ���󶥶ѣ������м�¼�Ĺؼ��ֶ��ԣ�
	int j;
	int rc;
	rc = H.elem[s];
	for (j = 2 * s; j <= m; j *= 2) {				// �عؼ��ֽϴ�ĺ��ӽ������ɸѡ
		if (j < m&&LT(H.elem[j], H.elem[j + 1])) {	// jΪ�ϴ�ļ�¼���±�
			++j;
		}
		if (!LT(rc, H.elem[j])) {
			break;
		}
		H.elem[s] = H.elem[j];
		s = j;
	}
	H.elem[s] = rc;									// ����
}// HeapAdjust

void HeapSort(HeapType &H) {
	// ��˳���H���ж�����
	int i;
	for (i = H.length / 2; i > 0; i--) {			// ��H.elem[1..H.length]���ɴ󶥶�
		HeapAdjust(H, i, H.length);
	}
	for (i = H.length; i > 1; --i) {	// �ѶѶ���¼�뵱ǰδ������������H.elem[1..i]�����һ��Ԫ�ؽ���
		Swap(H.elem[i], H.elem[1]);
		HeapAdjust(H, 1, i - 1);		// ��H.elem[1..i-1]���µ���Ϊ�󶥶�
	}
}// HeapSort