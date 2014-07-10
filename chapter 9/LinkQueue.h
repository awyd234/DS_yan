#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include "MyHeader.h"

//------------��������------------

typedef struct QNode{
	QElemType		data;
	struct QNode	*next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;	// ��ͷָ��
	QueuePtr rear;		//��βָ��
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead(LinkQueue Q, QElemType &e);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType));
Status Visit_Display_Int_LQ(QElemType e);

#endif