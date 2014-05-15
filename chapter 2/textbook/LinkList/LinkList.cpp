#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

void InitList_L(LinkList &L){
    //构造一个空的线性链表L
    L = (struct LNode *)malloc(sizeof(LNode));
    L->next = NULL;
}// InitList_L

void Destroy_L(LinkList &L){
    //销毁线性表L
    free(L);
    L = NULL;
}// Destroy_L

void ClearList_L(LinkList &L){
    //将L置为空表
    L->next = NULL;
}// ClearList_L

Status ListEmpty(LinkList L){
    //若L为空，返回TRUE，否则FALSE
    if(L->next) return FALSE;
    return TRUE;
}// ListEmpty

int ListLength_L(LinkList L){
    //返回L中元素个数
    LNode *p=L->next;
    int total = 0;
    while(p){
        total++;
        p = p->next;
    }
    return total;
}// ListLength_L

void CreateList_L(LinkList &L, int n){
    //逆序输入n个元素的值，建立带表头结点的单链线性表L
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

int LocateElme_L(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    //线性表L已存在，compare()为数据元素判定函数
    //返回L中第一个与e满足关系compare()的数据元素的位序。若这样的数据元素不存在，则返回值为0
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

Status ListDelete_L(LinkList &L, int i, ElemType &e){
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

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc){
    //已知单链线性表La与Lb的元素按值非递减排列
    //归并La与Lb得到新的单链线性表Lc，Lc的元素也按值非递减排列
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
    //遍历L中所有元素
    LNode *p = L->next;
    while(p){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}// ListTraverse_L

Status Display_L(ElemType e){
    //输出p的值
    printf("%d ",e);
    return OK;
}// Display_L

