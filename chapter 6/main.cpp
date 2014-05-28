#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

int main(){
	BiTree T;
	CreateBiTree(T);
	printf("PreOrderTraverse_Recur:\n");
	PreOrderTraverse_Recur(T, PrintElement);
	printf("\n\n");
	printf("InOrderTraverse_Recur:\n");
	InOrderTraverse_Recur(T, PrintElement);
	printf("\n\n");
	printf("PostOrderTraverse_Recur:\n");
	PostOrderTraverse_Recur(T, PrintElement);
	printf("\n\n");
	system("pause");
	return 0;
}