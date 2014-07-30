#ifndef _INSERT_SORT_H_
#define _INSERT_SORT_H_

#include "MyHeader.h"

//----- 静态链表的存储表示 -----
#define SIZE 100		// 静态链表容量

typedef struct {
	int key;			// 关键字
	int next;			// 指针项
}SLNode;				// 表结点类型

typedef struct {
	SLNode	r[SIZE];	// 0号单元为表头结点
	int length;			// 链表当前长度
}SLinkListType;			// 静态链表类型

Status CreateSqList(SqList &L, char *filename);
void InsertSort(SqList &L);
void BInsertSort(SqList &L);
void TwoInsertSort(SqList &L);
void TableInsertSort(SLinkListType &S);
Status CreateLinkList(SLinkListType &SL, char *filename);

#endif