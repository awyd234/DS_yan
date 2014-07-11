#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

int main(){
	SSTable ST;
	CreateTable(ST, 11, "test.txt");
	printf("%d\n", Search_Seq(ST, 65));
	system("pause");
	return 0;
}