#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

void SelectSort(SqList &L) {
	// 对顺序表L作简单选择排序
	int i, j;
	for (i = 1; i <= L.length; i++) {	// 选择第i小的记录，并交换到位
		j = SelectMinKey(L, i);			// 在L.elem[i..L.length]中选择最小的记录
		if (i != j) {
			Swap(L.elem[i], L.elem[j]);
		}
	}// for
}// SelectSort

int SelectMinKey(SqList L, int i) {
	// 在L.elem[i..L.length]中选择最小的记录
	int min = i;
	for (i++; i <= L.length; i++) {
		if (LT(L.elem[i], L.elem[min])) {
			min = i;
		}// if
	}// for
	return min;
}// SelectMinKey

void HeapAdjust(HeapType &H, int s, int m) {
	// 已知H.elem[s..m]中记录关键字除H.elem[s]之外均满足堆的定义，本函数调整H.elem[s]
	// 的关键字，使H.elem[s..m]成为又一个大顶堆（对其中记录的关键字而言）
	int j;
	int rc;
	rc = H.elem[s];
	for (j = 2 * s; j <= m; j *= 2) {				// 沿关键字较大的孩子结点向下筛选
		if (j < m&&LT(H.elem[j], H.elem[j + 1])) {	// j为较大的记录的下标
			++j;
		}
		if (!LT(rc, H.elem[j])) {
			break;
		}
		H.elem[s] = H.elem[j];
		s = j;
	}
	H.elem[s] = rc;									// 插入
}// HeapAdjust

void HeapSort(HeapType &H) {
	// 对顺序表H进行堆排序
	int i;
	for (i = H.length / 2; i > 0; i--) {			// 把H.elem[1..H.length]建成大顶堆
		HeapAdjust(H, i, H.length);
	}
	for (i = H.length; i > 1; --i) {	// 把堆顶记录与当前未经排序子序列H.elem[1..i]中最后一个元素交换
		Swap(H.elem[i], H.elem[1]);
		HeapAdjust(H, 1, i - 1);		// 将H.elem[1..i-1]重新调整为大顶堆
	}
}// HeapSort