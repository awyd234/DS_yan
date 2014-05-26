#include <stdlib.h>
#include <stdio.h>

#include "HString.h"
#include "algorithm.h"

int main(){
	HString S, T, V;
	S.ch = T.ch= V.ch = NULL;
	StrAssign(S, "asadas");
	StrAssign(S, "acabaabaabcacaabc");
	StrAssign(V, "12321");
	StrAssign(T, "abaabcac");
	printf("%d\n",Index_KMP(S, T, 1));
	//StrDelete(S, 2, 3);
	//StrInsert(S, 3, T);
	for (int i = 0; i < S.length; i++)
		printf("%c", S.ch[i]);
	printf("\n%d\n", StrLength(S));
	Destroy(S);
	Destroy(T);
	Destroy(V);
	system("pause");
	return 0;
}