#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

void CreateList_L(LinkList &L, int n){
    //��������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
    int i;
    LNode *p;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    printf("Please input %d numbers for the LinkList\n",n);
    for(i=n; i>0; i--){
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}// CreateList_L

Status GetElem_L(LinkList L, int i, ElemType &e){
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

Status ListInsert_L(LinkList &L, int i, ElemType e){
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

Status ListDelete_L(LinkList &L, int i, ElemType &e){
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

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc){
    //��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
    //�鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
    LNode *pa = La->next;
    LNode *pb = Lb->next;
    LNode *pc;
    Lc = pc = La;
    while(pa && pb){
        if(pa->data <= pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else{
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}// MergeList_L

void Print_L(LinkList &L){
    //˳�����L������Ԫ��
    LNode *p = L->next;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}// Print_L
