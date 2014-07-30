#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Status InitList_Sq(SqList &L)
{
    //����һ���յ����Ա�L
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(! L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

void DestroyList_Sq(SqList &L)
{
    //���Ա�L�Ѵ���
    //�������Ա�L
    free(L.elem);
    L.elem = NULL;
}// DestroyList_Sq

void ClearList_Sq(SqList &L)
{
    //���Ա�L�Ѵ���
    //��L��Ϊ�ձ�
    L.length = 0;
}// ClearList_Sq

Status ListEmpty_Sq(SqList L)
{
    //���Ա�L�Ѵ���
    //��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
    if(L.length == 0) return TRUE;
    else return FALSE;
}// ListEmpty_Sq

int ListLength_Sq(SqList L)
{
    //���Ա�L�Ѵ���
    //�������Ա���Ԫ�ظ���
    return L.length;
}// ListLength_Sq

Status GetElem_Sq(SqList L, int i, ElemType &e)
{
    //���Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)
    //��e����L�е�i������Ԫ�ص�ֵ
    //e = L+i-1;
    if(i < 1 || i > ListLength_Sq(L)) return ERROR;
    e = L.elem[i-1];
    return OK;
}// GetElem_Sq

Status compare_equal_Sq(ElemType e1, ElemType e2)
{
    //�Ƚ�e1��e2������ȷ���TRUE,���򷵻�FALSE
    if(e1 == e2) return TRUE;
    else return FALSE;
}// compare_equal_Sq

int LocateElme_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    //���Ա�L�Ѵ��ڣ�compare()Ϊ����Ԫ���ж�����
    //����L�е�һ����e�����ϵcompare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0
    for(int i=0; i<ListLength_Sq(L); i++)
        if(compare(L.elem[i],e))
            return i+1;
    return 0;
}// LocateElme_Sq

void PriorElem_Sq(SqList L, ElemType cure_e, ElemType &pre_e)
{
    //���Ա�L�Ѵ���
    //��cure_eΪL������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
    int pos;
    pos = LocateElme_Sq(L,cure_e,compare_equal_Sq);
    if(pos&&pos!=1)
        pre_e = *(L.elem+pos-2);
}// PriorElem_Sq

void NextElem_Sq(SqList L, ElemType cure_e, ElemType &next_e)
{
    //���Ա�L�Ѵ���
    //��cure_eΪL������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶���
    int pos;
    pos = LocateElme_Sq(L,cure_e,compare_equal_Sq);
    if(pos&&pos!=ListLength_Sq(L))
        next_e = *(L.elem + pos);
}// NextElem_Sq

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    //��˳�����Ա�L�еĵ�i��λ��֮ǰ�����µ�Ԫ��e
    //i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
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
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    //i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)
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
    //������Ա���Ԫ��e
    printf("%d ",e);
    return TRUE;
}// diplay_Sq

Status ListTraverse_Sq(SqList L,Status(*visit)(ElemType))
{
    //���Ա�L�Ѵ���
    //���ζ�L��ÿ������Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ��
    int i;
    for(i=1; i<=L.length; i++)
        if(!visit(*(L.elem+i)))
            return ERROR;
    return OK;
}// ListTraverse_Sq

void UnionList_Sq(SqList &La, SqList &Lb)
{
    //�����������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La��
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
    //��֪���Ա�La�����Ա�Lb��Ԫ�ذ�ֵ�ǵݼ�����
    //�鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
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
	// ����任L
	int i;
	for (i = 1; i <= (1 + L.length) / 2; i++) {
		Swap(L.elem[i], L.elem[L.length - i + 1]);
	}
}// InverseSq
