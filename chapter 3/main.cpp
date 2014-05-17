#include <stdio.h>
#include <stdlib.h>

#include "sq_stack.h"

int main(){
	SqStack S;
	InitStack(S);
	char test[] = "abcd?efg_hijk";
	for (int i = 0; test[i] != '\0'; i++)
		Push(S, test[i]);
	printf("Elements in S:\n");
	StackTraverse(S,Visit_Display_Char);
	SElemType e;
	Pop(S, e);
	printf("Pop:\n");
	StackTraverse(S, Visit_Display_Char);
	DestroyStack(S);
	system("pause");
	return OK;
}