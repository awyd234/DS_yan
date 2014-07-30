#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int hashsize[] = { 11, 13, 997 };	// 哈希表容量递增表，一个合适的素数序列

Status SearchHash(HashTable &H, KeyType K, int &p, int &c) {
	// 在开放定址哈希表H中查找关键字为K的元素，若查找成功，以p表示待查数据元素
	// 在表中位置，并返回SUCCESS，否则，以p指示插入位置，并返回UNSUCCESS，
	// c用以计冲突次数，其初值置零，供建表插入时参考
	c = 0;									// 冲突次数初始化
	p = Hash(K, hashsize[H.sizeindex]);		// 求得哈希地址
	while (H.elem[p].key != NULLKEY 		// 该位置中填有记录
		   && !EQ(K, H.elem[p].key)) {		// 且关键字不相等
		c++;								// 冲突次数加1
		if (c == hashsize[H.sizeindex]) {	// 哈希表已满，重建
			p = hashsize[H.sizeindex];		// 插入位置
			RecreateHashTable(H);			// 重建
			return UNSUCCESS;
		}
		collision(p, c, hashsize[H.sizeindex]);	// 求得下一探查地址p
	}
	if (EQ(K, H.elem[p].key)) {				// 查找成功
		return SUCCESS;
	} else {								// 查找失败
		return UNSUCCESS;
	}
}// SearchHash

int Hash(KeyType K, int p) {
	// 求得数据元素K的哈希地址，直接定址法
	return K%p;
}// Hash

Status collision(int &p, int c, int len) {
	// 生成下个位置，c为冲突次数，len为哈希表长，p为返回位置
	if (c == len) {
		return ERROR;
	} else {
		p = (p + c) % len;
		return OK;
	}
}// collision

Status InsertHash(HashTable &H, ElemType e) {
	// 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK；
	// 若冲突次数过大，重建哈希表
	int c, p;
	c = 0;
	if (SearchHash(H, e.key, p, c)) {
		return DUPLICATE;							// 表中已有与e相同关键字的元素
	} else if (c < hashsize[H.sizeindex] / 2) {		// 冲突次数未达上限（c阀值可调）
		H.elem[p] = e;								// 插入e
		H.count++;
		return OK;
	} else {
		RecreateHashTable(H);						// 重建哈希表
		return UNSUCCESS;
	}
}// InsertHash

Status CreateHashTable(HashTable &H, char *filename) {
	// 根据文件filename创建HashTable
	FILE *fp;
	ElemType e;
	if (!InitHashTable(H)) {
		return ERROR;
	}
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Fail to open the file: %s!", filename);
		return ERROR;
	}
	while (fscanf(fp, "%d", &e.key) != EOF) {
		InsertHash(H, e);
	}
	fclose(fp);
	return OK;
}// CreateHashTable

Status RecreateHashTable(HashTable &H) {
	// 重建哈希表H
	int i;
	H.elem = (ElemType *)realloc(H.elem, hashsize[H.sizeindex + 1] * sizeof(ElemType));
	if (!H.elem) {
		return ERROR;
	} else {
		for (int i = hashsize[H.sizeindex]; i < hashsize[H.sizeindex + 1]; i++) {
			H.elem[i].key = NULLKEY;
		}
		H.sizeindex++;
		return OK;
	}
}// RecreateHashTable

Status InitHashTable(HashTable &H) {
	// 初始化哈希表H
	H.sizeindex = 0;
	H.count = 0;
	H.elem = (ElemType *)malloc(hashsize[H.sizeindex] * sizeof(ElemType));
	if (!H.elem) {
		return ERROR;
	}
	for (int i = 0; i < hashsize[H.sizeindex]; i++) {
		H.elem[i].key = NULLKEY;
	}
	return OK;
}// InitHashTable

void DisplayHashTable(HashTable H) {
	// 打印哈希表H
	int i;
	for (i = 0; i < hashsize[H.sizeindex]; i++) {
		if (H.elem[i].key != NULLKEY) {
			printf("%d ", H.elem[i].key);
		}
	}
}// DisplayHashTable