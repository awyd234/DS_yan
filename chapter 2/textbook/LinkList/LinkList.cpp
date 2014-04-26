#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

void CreateList_L(LinkList &L, int n)
{
    //��������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
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
    //LΪ��ͷ���ĵ������ͷָ��
    //����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
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
    //�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
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
    //�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
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
