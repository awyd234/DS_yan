#include <stdlib.h>
#include <stdio.h>

#include "MyHeader.h"

int main(){
	HashTable H;
	CreateHashTable(H, "HASH_TABLE.txt");
	DisplayHashTable(H);
	printf("\n");
	system("pause");
	return 0;
}