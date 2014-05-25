#include <stdio.h>
#include <stdlib.h>

#include "LinkQueue.h"
#include "type_def.h"

Status InitQueue(LinkQueue &Q){
	// 构造一个空队列Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) return ERROR;
	Q.front->next = NULL;
	return OK;
}// InitQueue

Status DestroyQueue(LinkQueue &Q){
	// 销毁队列Q，Q不再存在
	while (Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}// DestroyQueue

Status ClearQueue(LinkQueue &Q){
	// 将Q清为空队列
	Q.rear = Q.front->next;
	while (Q.front->next){
		Q.rear = Q.rear->next;
		free(Q.front->next);
		Q.front->next = Q.rear;
	}
	Q.rear = Q.front;
	return OK;
}// ClearQueue

Status QueueEmpty(LinkQueue Q){
	// 若队列Q为空队列，则返回TRUE，否则返回FALSE
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}// QueueEmpty

int QueueLength(LinkQueue Q){
	// 返回Q的元素个数，即为队列的长度
	int len = 0;
	QueuePtr p = Q.front->next;
	while (p){
		len++;
		p = p->next;
	}
	return len;
}// QueueLength

SElemType GetHead(LinkQueue Q){
	// 若队列不为空，则返回Q的队列元素，否则返回ERROR
	if (Q.front == Q.rear) return ERROR;
	return Q.front->next->data;
}// GetHead

Status EnQueue(LinkQueue &Q, QElemType e){
	// 插入元素为e为Q的新的队尾元素
	QNode *p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}// EnQueue

Status DeQueue(LinkQueue &Q, QElemType &e){
	// 若队列不空，则返回Q的队头元素，用e返回其值，并返回OK
	// 否则返回ERROR
	if (Q.rear == Q.front) return ERROR;
	QNode *p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}// DeQueue

Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType)){
	// 从队头到队尾依次对队列Q中每个元素调用函数visit()，一旦visit失败，则操作失败
	QueuePtr p = Q.front->next;
	while (p){
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	printf("\n");
	return OK;
}// QueueTraverse

Status Visit_Display_Int_LQ(QElemType e){
	// 打印整型变量e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int