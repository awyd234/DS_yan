#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyHeader.h"

int PartionA(SqList &L, int low, int high) {
	// �任˳���L���ӱ�L.elem[low..high]�ļ�¼��ʹ��Ŧ��¼��λ��
	// ������������λ�ã���ʱ�������任ǰ���󣩵ļ�¼������С������
	// Comment�����ݽṹ���㷨����һ�����и��õĴ���������low,high��ֹͣ���ٽ��� 
	int pivotkey;
	pivotkey = L.elem[low];			// ���ӱ�ĵ�һ����¼����Ŧ��¼
	while (low < high) {			// �ӱ�����˽������м�ɨ��
		while (low < high&&L.elem[high] >= pivotkey) {
			--high;
		}
		Swap(L.elem[low], L.elem[high]);	// ������Ŧ��¼С��Ԫ�ؽ������Ͷ�
		while (low < high &&L.elem[low] <= pivotkey) {
			++low;
		}
		Swap(L.elem[low], L.elem[high]);	// ������Ŧ��¼���Ԫ�ؽ������߶�
	}
	return low; 
}// PartionA

int PartionB(SqList &L, int low, int high) {
	// �任˳���L���ӱ�L.elem[low..high]�ļ�¼��ʹ��Ŧ��¼��λ��
	// ������������λ�ã���ʱ�������任ǰ���󣩵ļ�¼������С������
	int pivotkey;
	L.elem[0] = L.elem[low];				// �ӱ�ĵ�һ��Ԫ������Ŧ��¼
	pivotkey = L.elem[low];					// ��Ŧ��¼�ؼ���
	while (low < high) {			// �ӱ�����˽������м�ɨ��
		while (low < high&&L.elem[high] >= pivotkey) {
			--high;
		}
		Swap(L.elem[low], L.elem[high]);	// ������Ŧ��¼С��Ԫ�ؽ������Ͷ�
		while (low < high &&L.elem[low] <= pivotkey) {
			++low;
		}
		Swap(L.elem[low], L.elem[high]);	// ������Ŧ��¼���Ԫ�ؽ������߶�
	}
	L.elem[low] = L.elem[0];				// ��Ŧ��¼��λ
	return low;								// ��Ŧ����λ��
}// PartionB

void QSort(SqList &L, int low, int high) {
	// ��˳���L�е�������L.elem[low..high]����������
	int pivotloc;
	if (low < high) {						// ���ȴ���1
		//pivotloc = PartionA(L, low, high);	// ��L.elem[low..high]һ��Ϊ��
		pivotloc = PartionB(L, low, high);	// ��L.elem[low..high]һ��Ϊ��
		QSort(L, low, pivotloc - 1);		// �Ե��ӱ�ݹ�����pivotloc����Ŧλ��
		QSort(L, pivotloc + 1, high);		// �Ը��ӱ�ݹ�����
	}
}// QSort

void QuickSort(SqList &L) {
	// ��˳���L����������
	QSort(L, 1, L.length);
}// QuickSort