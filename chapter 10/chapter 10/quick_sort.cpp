#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyHeader.h"

int PartionA(SqList &L, int low, int high) {
	// 变换顺序表L中子表L.elem[low..high]的记录，使枢纽记录到位，
	// 并返回其所在位置，此时，在它变换前（后）的记录均不大（小）于它
	// Comment：数据结构与算法分析一书中有更好的处理方法，等low,high都停止后再交换 
	int pivotkey;
	pivotkey = L.elem[low];			// 用子表的第一个记录作枢纽记录
	while (low < high) {			// 从表的两端交替向中间扫描
		while (low < high&&L.elem[high] >= pivotkey) {
			--high;
		}
		Swap(L.elem[low], L.elem[high]);	// 将比枢纽记录小的元素交换到低端
		while (low < high &&L.elem[low] <= pivotkey) {
			++low;
		}
		Swap(L.elem[low], L.elem[high]);	// 将比枢纽记录大的元素交换到高端
	}
	return low; 
}// PartionA

int PartionB(SqList &L, int low, int high) {
	// 变换顺序表L中子表L.elem[low..high]的记录，使枢纽记录到位，
	// 并返回其所在位置，此时，在它变换前（后）的记录均不大（小）于它
	int pivotkey;
	L.elem[0] = L.elem[low];				// 子表的第一个元素作枢纽记录
	pivotkey = L.elem[low];					// 枢纽记录关键字
	while (low < high) {			// 从表的两端交替向中间扫描
		while (low < high&&L.elem[high] >= pivotkey) {
			--high;
		}
		Swap(L.elem[low], L.elem[high]);	// 将比枢纽记录小的元素交换到低端
		while (low < high &&L.elem[low] <= pivotkey) {
			++low;
		}
		Swap(L.elem[low], L.elem[high]);	// 将比枢纽记录大的元素交换到高端
	}
	L.elem[low] = L.elem[0];				// 枢纽记录到位
	return low;								// 枢纽返回位置
}// PartionB

void QSort(SqList &L, int low, int high) {
	// 对顺序表L中的子序列L.elem[low..high]作快速排序
	int pivotloc;
	if (low < high) {						// 长度大于1
		//pivotloc = PartionA(L, low, high);	// 将L.elem[low..high]一分为二
		pivotloc = PartionB(L, low, high);	// 将L.elem[low..high]一分为二
		QSort(L, low, pivotloc - 1);		// 对低子表递归排序，pivotloc是枢纽位置
		QSort(L, pivotloc + 1, high);		// 对高子表递归排序
	}
}// QSort

void QuickSort(SqList &L) {
	// 对顺序表L作快速排序
	QSort(L, 1, L.length);
}// QuickSort