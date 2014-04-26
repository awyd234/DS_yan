#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

void CreateList_L(LinkList &L, int n)
{
    //逆序输入n个元素的值，建立带表头结点的单链线性表L
    int i;
    LNode *p;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for(i=n; i>0; i--){
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}// CreateList_L

Status GetElem_L(LinkList L, int i, ElemType &e)
{
    //L为带头结点的单链表的头指针
    //当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    LNode *p = L->next;
    int j =1;
    while(p && j<1){
        p = p->next;
        ++j;
    }
    if(!p || j>i) return ERROR;
    e = p->data;
    return OK;
}// Status GetElem_L

Status ListInsert_L(LinkList &L, int i, ElemType e)
{
    //在带头结点的单链线性表L中第i个位置之前插入元素e
    LNode *p = L;
    int j = 0;
    while(p && j<i-1){
        p = p->next;
        ++j;
    }
    if(!p || j>i-1) return ERROR;
    LNode *s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}// ListInsert_L

Status ListDelete_L(LinkList &L, int i, ElemType e)
{
    //在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
    LNode *p = L;
    int j = 0;
    while(p->next && j<i-1){
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i-1) return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}// ListDelete_L
