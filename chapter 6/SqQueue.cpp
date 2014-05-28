#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status InitQueue(SqQueue &Q){
	// 构造一个空队列Q
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) return ERROR;
	Q.front = Q.rear = 0;
	return OK;
}// InitQueue

Status DestroyQueue(SqQueue &Q){
	// 销毁队列
	free(Q.base);
	Q.base = NULL;
	return OK;
}// DestroyQueue

int QueueLength(SqQueue Q){
	// 返回Q的元素个数，即队列的长度
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}// QueueLength

Status ClearQueue(SqQueue &Q){
	// 将Q清为空队列
	Q.rear = Q.front = 0;
	return OK;
}// ClearQueue

Status QueueEmpty(SqQueue Q){
	// 若队列Q为空队列，则返回TRUE，否则返回FALSE
	if (Q.rear == Q.front) 
		return TRUE;
	else
		return FALSE;
}// QueueEmpty

SElemType GetHead(SqQueue Q){
	// 若队列不为空，则返回Q的队列元素，否则返回ERROR
	if (Q.rear == Q.front) return ERROR;
	return *(Q.base + Q.front);
}// GetHead

Status EnQueue(SqQueue &Q, QElemType e){
	// 插入元素e为Q的新的队尾元素
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}// EnQueue

Status DeQueue(SqQueue &Q, QElemType &e){
	// 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
	// 否则返回ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}// DeQueue

Status QueueTraverse(SqQueue Q, Status(*visit)(QElemType)){
	// 从队头到队尾依次对队列Q中每个元素调用函数visit()，一旦visit失败，则操作失败
	int p = Q.front;
	while (p != Q.rear){
		if (!(*visit)(*(Q.base + p)))
			return ERROR;
		p = (p + 1) % MAXQSIZE;
	}
	printf("\n");
	return OK;
}// QueueTraverse

Status Visit_Display_Int_SQ(QElemType e){
	// 打印整型变量e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int_SQ