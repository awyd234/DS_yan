#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int main() {
	SqList L;
	CreateSqList(L, "SqList_Data.txt");
	//InsertSort(L);
	//BInsertSort(L);
	//TwoInsertSort(L);
	int dlta[30] = { 2, 1 };
	ShellSort(L, dlta, 2);
	ListTraverse_Sq(L, display_Sq);
	//DestroyList_Sq(L);
	/*SLinkListType SL;
	CreateLinkList(SL, "SqList_Data.txt");
	TableInsertSort(SL);
	Arrange(SL);
	for (int i = 1; i <= SL.length; i++) {
		printf("%d ", SL.r[i].key);
	}*/
	printf("\n");
	system("pause");
	return 0;
}