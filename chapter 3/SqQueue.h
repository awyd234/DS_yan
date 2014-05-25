#ifndef _SQQUEUE_H_
#define _SQQUEUE_H_

//---------- ѭ�����С������е�˳��洢�ṹ ----------
#include "type_def.h"

#define MAXQSIZE 100	// �����г���
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