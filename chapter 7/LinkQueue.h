#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

//------------定义链队------------
#include "type_def.h"

typedef struct QNode{
	QElemType		data;
	struct QNode	*next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;	// 队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
QElemType GetHead(LinkQueue Q);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType));
Status Visit_Display_Int_LQ(QElemType e);

#endif