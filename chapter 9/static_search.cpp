#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MyHeader.h"

Status CreateTable(SSTable &ST, int n, char *filename){
	// ����һ����n������Ԫ�صľ�̬���ұ�ST
	int i;
	FILE *pfile;
	ST.length = n;
	if (!(ST.elem = (ElemType *)malloc((n + 1)*sizeof(ElemType)))){
		return ERROR;
	}
	if (!(pfile = fopen(filename, "r"))){
		printf("Fail to open the file %s!!!\n", filename);
		return FILE_NOT_EXIT;
	}
	for (i = 1; i < n; i++){
		if (EOF == fscanf(pfile, "%d %s %f", 
			&ST.elem[i].key, &ST.elem[i].data, &ST.elem[i].weight)){
			printf("Fail to read the record!!!\n",i,filename,ST.length);
			return ERROR;
		}
	}
	fclose(pfile);
	return OK;
}// CreateTable

void Destroy(SSTable &ST){
	// ����̬���ұ�ST���ڣ�����ST
	if (!ST.elem){
		free(ST.elem);
		ST.elem = NULL;
		ST.length = 0;
	}
}// Destroy

int Search_Seq(SSTable ST, KeyType key){
	// ��˳���ST��˳��˳�������ؼ��ֵ���key������Ԫ�أ����ҵ�������ֵΪ
	// ��Ԫ���ڱ���λ�ã�����Ϊ0
	int i;
	ST.elem[0].key = key;									// �ڱ�
	for (i = ST.length; !EQ(ST.elem[i].key, key); --i);		// �Ӻ���ǰ��
	return i;												// �Ҳ���ʱiΪ0
}// Search_Seq

int Search_Bin(SSTable ST, KeyType key){
	// �������ST���۰������ؼ��ֵ���key������Ԫ�أ����ҵ�������ֵΪ��Ԫ��
	// �ڱ��е�λ�ã�����Ϊ0
	int low, high, mid;
	low = 1;									// �������ֵ
	high = ST.length;
	while (low < high){
		mid = (low + high) / 2;	
		if (EQ(key, ST.elem[mid].key)){			// �ҵ�����Ԫ��
			return mid;
		} else if (LT(key, ST.elem[mid].key)){	// ������ǰ��������в���
			high = mid - 1;
		} else{									// �����ں��������в���
			low = mid + 1;
		}
	}
	return 0;									// ˳����в����ڴ���Ԫ��
}// Search_Bin

void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high){
	// �������R[low...high]�����ۼ�Ȩֵ��sw������sw[0]==0���ݹ鹹����Ų�����T
	int i, j;
	float min, dw;
	i = low;
	min = abs(sw[high] - sw[low]);
	dw = sw[high] + sw[low - 1];
	for (j = low + 1; j <= high; ++j){					// ѡ����С�ġ�Pi��ֵ
		if (abs(dw - sw[j] - sw[j - 1]) < min){
			i = j;
			min = abs(dw - sw[j] - sw[j - 1]);
		}
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = R[i];										// ���ɽ��
	if (i == low){
		T->lchild = NULL;								// ������Ϊ�� 
	} else{
		SecondOptimal(T->lchild, R, sw, low, i - 1);	// ����������
	}
	if (i == high){
		T->rchild = NULL;								// ������Ϊ��
	} else{
		SecondOptimal(T->rchild, R, sw, i + 1, high);	// ����������
	}
}// SecondOptimal

void FindSW(ElemType R[], float sw[], int length){
	// ���������ST�и�����Ԫ�ص�weight�����ۻ�Ȩֵ��sw
	int i;
	sw[0] = 0;
	for (i = 1; i <= length; i++){
		sw[i] = sw[i - 1] + R[i].weight;
	}
}// FindSW

Status CreateSOSTree(SOSTree &T, SSTable ST){
	// �������ST����һ�ô��Ų�����T��ST������Ԫ�غ���Ȩ��weight
	float *sw;
	if (!(sw = (float *)malloc((ST.length + 1)*sizeof(float)))){
		return NULL;
	}
	if (ST.length == 0){
		T = NULL;
	} else{
		FindSW(ST.elem, sw, ST.length);		// ���������ST�и�����Ԫ�ص�weight�����ۻ�Ȩֵ��sw
		SecondOptimal(T, ST.elem, sw, 1, ST.length);
	}
	return OK;
}// CreateSOSTree 