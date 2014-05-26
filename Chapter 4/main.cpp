#include <stdlib.h>
#include <stdio.h>

#include "HString.h"

int main(){
	HString S;
	S.ch = NULL;
	StrAssign(S, "asadas");
	StrAssign(S, "asadasasdsadas");
	printf("%d\n", StrLength(S));
	system("pause");
	return 0;
}