#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int main() {
	//SqList L;
	//CreateSqList(L, "SqList_Data.txt");
	//InsertSort(L);
	//BInsertSort(L);
	//TwoInsertSort(L);
	//int dlta[30] = { 2, 1 };
	//ShellSort(L, dlta, 2);
	//QuickSort(L);
	//SelectSort(L);
	//InverseSq(L);
	//HeapSort(L);
	//MergeSort(L);
	//ListTraverse_Sq(L, display_Sq);
	//DestroyList_Sq(L);
	/*SLinkListType SL;
	CreateLinkList(SL, "SqList_Data.txt");
	TableInsertSort(SL);
	Arrange(SL);
	for (int i = 1; i <= SL.length; i++) {
		printf("%d ", SL.r[i].key);
	}*/
	SLList L;
	CreateRadixSort(L, "RADIX_DATA.txt");
	RadixSort(L);
	for (int i = L.r[0].next; i; i = L.r[i].next) {
		printf("%d ", L.r[i].keys[2] * 100 + L.r[i].keys[1] * 10 + L.r[i].keys[0]);
	}
	printf("\n");
	system("pause");
	return 0;
}