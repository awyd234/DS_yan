#include <stdio.h>
#include <stdlib.h>

#include "SqQueue.h"

int main(){
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	QueueTraverse(Q, Visit_Display_Int_SQ);
	QElemType e;
	DeQueue(Q,e);
	QueueTraverse(Q,Visit_Display_Int_SQ);
	DestroyQueue(Q);
	system("pause");
	return 0;
}