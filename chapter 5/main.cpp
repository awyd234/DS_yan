#include <stdlib.h>
#include <stdio.h>

#include "array.h"

int main(){
	Array A;
	InitArray(A, 3, 1, 2, 3);
	int i, j, k, off;
	ElemType count = 0;
	for (i = 0; i < 1; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 3; k++, count++)
				Value(A, count, i, j, k);
	Destroy(A);
	system("pause");
	return 0;
}