#include <stdio.h>
#include <stdlib.h>

#include "LinkQueue.h"

int main(){
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	EnQueue(Q, 4);
	ClearQueue(Q);
	EnQueue(Q, 4);
	QueueTraverse(Q, Visit_Display_Int_LQ);
	DestroyQueue(Q);
	system("pause");
	return OK;
}