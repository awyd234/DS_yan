#ifndef _SELECT_SORT_H_
#define _SELECT_SORT_H_

#include "MyHeader.h"

typedef SqList HeapType;			// �Ѳ���˳���洢��ʾ

void SelectSort(SqList &L);
int SelectMinKey(SqList L, int i);
void HeapAdjust(HeapType &H, int s, int m);
void HeapSort(HeapType &H);

#endif