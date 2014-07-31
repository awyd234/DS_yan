#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

#include "radix_sort.h"

#define MAX_NUM_OF_KEY	8	// �ؼ������������ֵ
#define RADIX			10	// �ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE	10000	//

typedef int KeysType;
typedef char *InfoType;

typedef struct {
	KeysType keys[MAX_NUM_OF_KEY];	// �ؼ���
	InfoType otheritems;			// ����������
	int next;
}SLCell;							// ��̬����Ľ������

typedef struct {
	SLCell	r[MAX_SPACE];			// ��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
	int		keynum;					// ��¼��ǰ�Ĺؼ��ָ���
	int		recnum;					// ��̬����ĵ�ǰ����
}SLList;							// ��̬��������

typedef int ArrType[RADIX];			// ָ����������

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e);
int ord(ElemType K);
void Collect(SLCell r[], int i, ArrType f, ArrType e);
int succ(ArrType f, int j);
void RadixSort(SLList &L);
Status CreateRadixSort(SLList &L, char *filename);

#endif