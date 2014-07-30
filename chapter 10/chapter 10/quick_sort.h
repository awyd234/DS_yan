#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include "MyHeader.h"

int PartionA(SqList &L, int low, int high);
int PartionB(SqList &L, int low, int high);
void QSort(SqList &L, int low, int high);
void QuickSort(SqList &L);

#endif