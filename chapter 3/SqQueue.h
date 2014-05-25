#ifndef _SQQUEUE_H_
#define _SQQUEUE_H_

//---------- 循环队列——队列的顺序存储结构 ----------
#include "type_def.h"

#define MAXQSIZE 100	// 最大队列长度
typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &Q);
Status DestroyQueue(SqQueue &Q);
Status ClearQueue(SqQueue &Q);
Status QueueEmpty(SqQueue Q);
int QueueLength(SqQueue Q);
SElemType GetHead(SqQueue Q);
Status EnQueue(SqQueue &Q, QElemType e);
Status DeQueue(SqQueue &Q, QElemType &e);
Status QueueTraverse(SqQueue Q, Status(*visit)(QElemType));
Status Visit_Display_Int_SQ(QElemType e);

#endif