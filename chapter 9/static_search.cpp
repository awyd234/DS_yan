#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "MyHeader.h"

Status CreateTable(SSTable &ST, int n, char *filename){
	// 构造一个含n个数据元素的静态查找表ST
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
	// 若静态查找表ST存在，销毁ST
	if (!ST.elem){
		free(ST.elem);
		ST.elem = NULL;
		ST.length = 0;
	}
}// Destroy

int Search_Seq(SSTable ST, KeyType key){
	// 在顺序表ST中顺序顺序查找其关键字等于key的数据元素，若找到，则函数值为
	// 该元素在表中位置，否则为0
	int i;
	ST.elem[0].key = key;									// 哨兵
	for (i = ST.length; !EQ(ST.elem[i].key, key); --i);		// 从后往前找
	return i;												// 找不到时i为0
}// Search_Seq

int Search_Bin(SSTable ST, KeyType key){
	// 在有序表ST中折半查找其关键字等于key的数据元素，若找到，则函数值为该元素
	// 在表中的位置，否则为0
	int low, high, mid;
	low = 1;									// 置区间初值
	high = ST.length;
	while (low < high){
		mid = (low + high) / 2;	
		if (EQ(key, ST.elem[mid].key)){			// 找到待查元素
			return mid;
		} else if (LT(key, ST.elem[mid].key)){	// 继续在前半区间进行查找
			high = mid - 1;
		} else{									// 继续在后半区间进行查找
			low = mid + 1;
		}
	}
	return 0;									// 顺序表中不存在待查元素
}// Search_Bin

void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high){
	// 由有序表R[low...high]及其累计权值表sw（其中sw[0]==0）递归构造次优查找树T
	int i, j;
	float min, dw;
	i = low;
	min = abs(sw[high] - sw[low]);
	dw = sw[high] + sw[low - 1];
	for (j = low + 1; j <= high; ++j){					// 选择最小的△Pi的值
		if (abs(dw - sw[j] - sw[j - 1]) < min){
			i = j;
			min = abs(dw - sw[j] - sw[j - 1]);
		}
	}
	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = R[i];										// 生成结点
	if (i == low){
		T->lchild = NULL;								// 左子树为空 
	} else{
		SecondOptimal(T->lchild, R, sw, low, i - 1);	// 构造左子树
	}
	if (i == high){
		T->rchild = NULL;								// 右子树为空
	} else{
		SecondOptimal(T->rchild, R, sw, i + 1, high);	// 构造右子树
	}
}// SecondOptimal

void FindSW(ElemType R[], float sw[], int length){
	// 按照有序表ST中各数据元素的weight域求累积权值表sw
	int i;
	sw[0] = 0;
	for (i = 1; i <= length; i++){
		sw[i] = sw[i - 1] + R[i].weight;
	}
}// FindSW

Status CreateSOSTree(SOSTree &T, SSTable ST){
	// 由有序表ST构造一棵次优查找树T。ST的数据元素含有权域weight
	float *sw;
	if (!(sw = (float *)malloc((ST.length + 1)*sizeof(float)))){
		return NULL;
	}
	if (ST.length == 0){
		T = NULL;
	} else{
		FindSW(ST.elem, sw, ST.length);		// 按照有序表ST中各数据元素的weight域求累积权值表sw
		SecondOptimal(T, ST.elem, sw, 1, ST.length);
	}
	return OK;
}// CreateSOSTree 