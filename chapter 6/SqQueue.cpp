#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status InitQueue(SqQueue &Q){
	// ����һ���ն���Q
	Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) return ERROR;
	Q.front = Q.rear = 0;
	return OK;
}// InitQueue

Status DestroyQueue(SqQueue &Q){
	// ���ٶ���
	free(Q.base);
	Q.base = NULL;
	return OK;
}// DestroyQueue

int QueueLength(SqQueue Q){
	// ����Q��Ԫ�ظ����������еĳ���
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}// QueueLength

Status ClearQueue(SqQueue &Q){
	// ��Q��Ϊ�ն���
	Q.rear = Q.front = 0;
	return OK;
}// ClearQueue

Status QueueEmpty(SqQueue Q){
	// ������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	if (Q.rear == Q.front) 
		return TRUE;
	else
		return FALSE;
}// QueueEmpty

SElemType GetHead(SqQueue Q){
	// �����в�Ϊ�գ��򷵻�Q�Ķ���Ԫ�أ����򷵻�ERROR
	if (Q.rear == Q.front) return ERROR;
	return *(Q.base + Q.front);
}// GetHead

Status EnQueue(SqQueue &Q, QElemType e){
	// ����Ԫ��eΪQ���µĶ�βԪ��
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}// EnQueue

Status DeQueue(SqQueue &Q, QElemType &e){
	// �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
	// ���򷵻�ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}// DeQueue

Status QueueTraverse(SqQueue Q, Status(*visit)(QElemType)){
	// �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���visit()��һ��visitʧ�ܣ������ʧ��
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
	// ��ӡ���ͱ���e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int_SQ