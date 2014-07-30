#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

int main(){
	BTree T;
	T = NULL;
	CreateBTree(T, "BTree_Data.txt");
	DisplayBTree(T);
	printf("\n");
	system("pause");
	return 0;
}