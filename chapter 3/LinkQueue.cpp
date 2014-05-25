#include <stdio.h>
#include <stdlib.h>

#include "LinkQueue.h"
#include "type_def.h"

Status InitQueue(LinkQueue &Q){
	// ����һ���ն���Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) return ERROR;
	Q.front->next = NULL;
	return OK;
}// InitQueue

Status DestroyQueue(LinkQueue &Q){
	// ���ٶ���Q��Q���ٴ���
	while (Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}// DestroyQueue

Status ClearQueue(LinkQueue &Q){
	// ��Q��Ϊ�ն���
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
	// ������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}// QueueEmpty

int QueueLength(LinkQueue Q){
	// ����Q��Ԫ�ظ�������Ϊ���еĳ���
	int len = 0;
	QueuePtr p = Q.front->next;
	while (p){
		len++;
		p = p->next;
	}
	return len;
}// QueueLength

SElemType GetHead(LinkQueue Q){
	// �����в�Ϊ�գ��򷵻�Q�Ķ���Ԫ�أ����򷵻�ERROR
	if (Q.front == Q.rear) return ERROR;
	return Q.front->next->data;
}// GetHead

Status EnQueue(LinkQueue &Q, QElemType e){
	// ����Ԫ��ΪeΪQ���µĶ�βԪ��
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
	// �����в��գ��򷵻�Q�Ķ�ͷԪ�أ���e������ֵ��������OK
	// ���򷵻�ERROR
	if (Q.rear == Q.front) return ERROR;
	QNode *p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return OK;
}// DeQueue

Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType)){
	// �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���visit()��һ��visitʧ�ܣ������ʧ��
	QueuePtr p = Q.front->next;
	while (p){
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	printf("\n");
	return OK;
}// QueueTraverse

Status Visit_Display_Int_LQ(QElemType e){
	// ��ӡ���ͱ���e
	printf("%d ", e);
	return OK;
}// Visit_Display_Int