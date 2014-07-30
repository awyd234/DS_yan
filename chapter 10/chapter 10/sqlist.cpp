#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status InitList_Sq(SqList &L)
{
    //构造一个空的线性表L
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(! L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

void DestroyList_Sq(SqList &L)
{
    //线性表L已存在
    //销毁线性表L
    free(L.elem);
    L.elem = NULL;
}// DestroyList_Sq

void ClearList_Sq(SqList &L)
{
    //线性表L已存在
    //将L置为空表
    L.length = 0;
}// ClearList_Sq

Status ListEmpty_Sq(SqList L)
{
    //线性表L已存在
    //若L为空表，则返回TRUE，否则返回FALSE
    if(L.length == 0) return TRUE;
    else return FALSE;
}// ListEmpty_Sq

int ListLength_Sq(SqList L)
{
    //线性表L已存在
    //返回线性表中元素个数
    return L.length;
}// ListLength_Sq

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
    //线性表L已存在，1<=i<=ListLength(L)
    //用e返回L中第i个数据元素的值
    //e = L+i-1;
    if(i < 1 || i > ListLength_Sq(L)) return ERROR;
    e = L.elem[i-1];
    return OK;
}// GetElem_Sq

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
    //比较e1与e2，若相等返回TRUE,否则返回FALSE
    if(e1 == e2) return TRUE;
    else return FALSE;
}// compare_equal_Sq

int LocateElme_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    //线性表L已存在，compare()为数据元素判定函数
    //返回L中第一个与e满足关系compare()的数据元素的位序。若这样的数据元素不存在，则返回值为0
    for(int i=0; i<ListLength_Sq(L); i++)
        if(compare(L.elem[i],e))
            return i+1;
    return 0;
}// LocateElme_Sq

void PriorElem_Sq(SqList L, ElemType cure_e, ElemType &pre_e)
{
    //线性表L已存在
    //若cure_e为L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
    int pos;
    pos = LocateElme_Sq(L,cure_e,compare_equal_Sq);
    if(pos&&pos!=1)
        pre_e = *(L.elem+pos-2);
}// PriorElem_Sq

void NextElem_Sq(SqList L, ElemType cure_e, ElemType &next_e)
{
    //线性表L已存在
    //若cure_e为L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义
    int pos;
    pos = LocateElme_Sq(L,cure_e,compare_equal_Sq);
    if(pos&&pos!=ListLength_Sq(L))
        next_e = *(L.elem + pos);
}// NextElem_Sq

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    //在顺序线性表L中的第i个位置之前插入新的元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
	int j;
    if(L.length+2 >= L.listsize){
        int *newbase = (ElemType *)realloc(L.elem,
                        (L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
	for (j = L.length + 1; j >= i; j--) {
		*(L.elem + j) = *(L.elem + j - 1);
	}
	*(L.elem + i - 1) = e;
    ++L.length;
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    //在顺序线性表L中删除第i个元素，并用e返回其值
    //i的合法值为1<=i<=ListLength_Sq(L)
    if((i < 1) || (i > L.length)) return ERROR;
    int *p = & (L.elem[i-1]);
    e = *p;
    int *q = L.elem + L.length - 1;
    for(++p; p <= q; ++p) *(p-1) = *p;
    --L.length;
    return OK;
}// ListDelete_Sq

Status display_Sq(ElemType e)
{
    //输出线性表中元素e
    printf("%d ",e);
    return TRUE;
}// diplay_Sq

Status ListTraverse_Sq(SqList L,Status(*visit)(ElemType))
{
    //线性表L已存在
    //依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败
    int i;
    for(i=1; i<=L.length; i++)
        if(!visit(*(L.elem+i)))
            return ERROR;
    return OK;
}// ListTraverse_Sq

void UnionList_Sq(SqList &La, SqList &Lb)
{
    //将所有在线性表Lb中但不在La中的数据元素插入到La中
    int La_len = ListLength_Sq(La);
    int Lb_len = ListLength_Sq(Lb);
    ElemType e;
    for(int i = 1; i <= Lb_len; i++){
        GetElem_Sq(Lb, i, e);
        if(!LocateElme_Sq(La, e, compare_equal_Sq)) ListInsert_Sq(La, ++La_len, e);
    }
}// unionList_Sq

void Merge_Sq(SqList La,SqList Lb, SqList &Lc)
{
    //已知线性表La与线性表Lb的元素按值非递减排列
    //归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
    ElemType *pa = La.elem;
    ElemType *pb = Lb.elem;
    ElemType *pc = Lc.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    if(!Lc.elem) exit(OVERFLOW);
    ElemType *pa_last = La.elem + La.length -1;
    ElemType *pb_last = Lb.elem + Lb.length -1;
    while(pa<=pa_last && pb<=pb_last){
        if(*pa <= *pb) *pc++=*pa++;
        else *pc++=*pb++;
    }
    while(pa <= pa_last) *pc++=*pa++;
    while(pb <= pb_last) *pc++=*pb++;
}// Merge_Sq

void InverseSq(SqList &L) {
	// 逆向变换L
	int i;
	for (i = 1; i <= (1 + L.length) / 2; i++) {
		Swap(L.elem[i], L.elem[L.length - i + 1]);
	}
}// InverseSq
