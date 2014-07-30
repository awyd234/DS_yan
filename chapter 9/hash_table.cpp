#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

int hashsize[] = { 11, 13, 997 };	// ��ϣ������������һ�����ʵ���������

Status SearchHash(HashTable &H, KeyType K, int &p, int &c) {
	// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ�أ������ҳɹ�����p��ʾ��������Ԫ��
	// �ڱ���λ�ã�������SUCCESS��������pָʾ����λ�ã�������UNSUCCESS��
	// c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο�
	c = 0;									// ��ͻ������ʼ��
	p = Hash(K, hashsize[H.sizeindex]);		// ��ù�ϣ��ַ
	while (H.elem[p].key != NULLKEY 		// ��λ�������м�¼
		   && !EQ(K, H.elem[p].key)) {		// �ҹؼ��ֲ����
		c++;								// ��ͻ������1
		if (c == hashsize[H.sizeindex]) {	// ��ϣ���������ؽ�
			p = hashsize[H.sizeindex];		// ����λ��
			RecreateHashTable(H);			// �ؽ�
			return UNSUCCESS;
		}
		collision(p, c, hashsize[H.sizeindex]);	// �����һ̽���ַp
	}
	if (EQ(K, H.elem[p].key)) {				// ���ҳɹ�
		return SUCCESS;
	} else {								// ����ʧ��
		return UNSUCCESS;
	}
}// SearchHash

int Hash(KeyType K, int p) {
	// �������Ԫ��K�Ĺ�ϣ��ַ��ֱ�Ӷ�ַ��
	return K%p;
}// Hash

Status collision(int &p, int c, int len) {
	// �����¸�λ�ã�cΪ��ͻ������lenΪ��ϣ����pΪ����λ��
	if (c == len) {
		return ERROR;
	} else {
		p = (p + c) % len;
		return OK;
	}
}// collision

Status InsertHash(HashTable &H, ElemType e) {
	// ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK��
	// ����ͻ���������ؽ���ϣ��
	int c, p;
	c = 0;
	if (SearchHash(H, e.key, p, c)) {
		return DUPLICATE;							// ����������e��ͬ�ؼ��ֵ�Ԫ��
	} else if (c < hashsize[H.sizeindex] / 2) {		// ��ͻ����δ�����ޣ�c��ֵ�ɵ���
		H.elem[p] = e;								// ����e
		H.count++;
		return OK;
	} else {
		RecreateHashTable(H);						// �ؽ���ϣ��
		return UNSUCCESS;
	}
}// InsertHash

Status CreateHashTable(HashTable &H, char *filename) {
	// �����ļ�filename����HashTable
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
	// �ؽ���ϣ��H
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
	// ��ʼ����ϣ��H
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
	// ��ӡ��ϣ��H
	int i;
	for (i = 0; i < hashsize[H.sizeindex]; i++) {
		if (H.elem[i].key != NULLKEY) {
			printf("%d ", H.elem[i].key);
		}
	}
}// DisplayHashTable