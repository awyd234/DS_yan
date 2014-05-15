#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

void InitList_L(LinkList &L){
    //����һ���յ���������L
    L = (struct LNode *)malloc(sizeof(LNode));
    L->next = NULL;
}// InitList_L

void Destroy_L(LinkList &L){
    //�������Ա�L
    free(L);
    L = NULL;
}// Destroy_L

void ClearList_L(LinkList &L){
    //��L��Ϊ�ձ�
    L->next = NULL;
}// ClearList_L

Status ListEmpty(LinkList L){
    //��LΪ�գ�����TRUE������FALSE
    if(L->next) return FALSE;
    return TRUE;
}// ListEmpty

int ListLength_L(LinkList L){
    //����L��Ԫ�ظ���
    LNode *p=L->next;
    int total = 0;
    while(p){
        total++;
        p = p->next;
    }
    return total;
}// ListLength_L

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

int LocateElme_L(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    //���Ա�L�Ѵ��ڣ�compare()Ϊ����Ԫ���ж�����
    //����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0
    LNode *p=L->next;
    int i=0;
    while(p){
        i++;
        if(p->data==e) return i;
        p = p->next;
    }
    return 0;
}// LocateElme_L

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

void ListTraverse_L(LinkList &L, Status(*visit)(ElemType)){
    //����L������Ԫ��
    LNode *p = L->next;
    while(p){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}// ListTraverse_L

Status Display_L(ElemType e){
    //���p��ֵ
    printf("%d ",e);
    return OK;
}// Display_L

