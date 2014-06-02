#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

int main(){
	BiThrTree T,Thrt;
	CreateBiThrTree(T);
	InOrderThreading(Thrt, T);
	InOrderTraverse_Thr(T, PrintElement);
	printf("\n");
	system("pause");
	return 0;
}