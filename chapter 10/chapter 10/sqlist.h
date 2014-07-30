#ifndef _SQLIST_H_
#define _SQLIST_H_

#include "MyHeader.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct{
    ElemType *elem; //存储空间基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;

Status InitList_Sq(SqList &L);
void DestroyList_Sq(SqList &L);
void ClearList_Sq(SqList &L);
Status ListEmpty_Sq(SqList L);
int ListLength_Sq(SqList L);
Status GetElem_Sq(SqList L, int i, ElemType &e);
Status compare_equal_Sq(ElemType e1, ElemType e2);
int LocateElme_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType));
void PriorElem_Sq(SqList L, ElemType cure_e, ElemType &pre_e);
void NextElem_Sq(SqList L, ElemType cure_e, ElemType &next_e);
Status ListInsert_Sq(SqList &L, int i, ElemType e);
Status ListDelete_Sq(SqList &L, int i, ElemType &e);
Status ListTraverse_Sq(SqList L,Status(*visit)(ElemType));
Status display_Sq(ElemType e);

void UnionList_Sq(SqList &La, SqList &Lb);
void Merge_Sq(SqList La,SqList Lb, SqList &Lc);

#endif
