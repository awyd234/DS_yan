#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MyHeader.h"

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	// w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC��
	int m, i, s1, s2, start, c, f;
	char *cd;
	HuffmanTree p;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) *sizeof(HTNode));	// 0�ŵ�Ԫδ��
	for (p = HT, i = 1; i <= n; ++i, ++p, ++w)
		*p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		*p = { 0, 0, 0, 0 };
	for (i = n + 1; i < m; ++i){
		// ��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1����s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//----- ��Ҷ�ӵ���������ÿ���ַ��ĺշ������� -----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));		// ����n���ַ������ͷָ������
	cd = (char *)malloc(n * sizeof(char));			// ���������Ĺ����ռ�
	cd[n - 1] = '\0';								// �༭������
	for (i = 1; i <= n; ++i){						// ����ַ���շ�������
		start = n - 1;								// ���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent){	// ��Ҷ�ӵ������������
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));	// Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);				// ��cd���Ʊ��루������HC
	}
	free(cd);					// �ͷŹ����ռ�
}// HuffmanCoding

void Select(HuffmanTree &HT, int n, int &s1, int &s2){
	// ��HT[1...n]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1����s2
	int i;
	s1 = s2 = 0;
	for (i = 1; i <= n && (s1 == 0 || s2 == 0); i++){
		if (HT[i].parent == 0){
			if (s1 == 0){
				s1 = i;
			} else{
				s2 = i;
			}
		}
	}
	if (HT[s1].weight > HT[s2].weight){
		s1 = s1 + s2;
		s2 = s1 - s2;
		s1 = s1 - s2;
	}
	for (; i <= n; i++){
		if (HT[i].parent == 0){
			if (HT[i].weight < HT[s2].weight){
				if (HT[i].weight < HT[s1].weight){
					s2 = s1;
					s1 = i;
				} else{
					s2 = i;
				}
			}
		}
	}
}// Select

void GetHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
	//��ջ�ǵݹ�����շ���������շ�������
	int m, p, cdlen, i;
	char *cd;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	cd = (char *)malloc(n*sizeof(char));
	m = 2 * n - 1;
	p = m;
	cdlen = 0;
	for (i = 1; i <= m; ++i)		// �����շ�����ʱ�������״̬��־
		HT[i].weight = 0;
	while (p){
		if (HT[p].weight == 0){		// ����
			HT[p].weight = 1;
			if (HT[p].lchild != 0){
				p = HT[p].lchild;
				cd[cdlen++] = '0';
			} else if (HT[p].rchild == 2){		// �Ǽ�Ҷ�ӽ����ַ��ı���
				HC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[p], cd);		// ���Ʊ��루����
			}
		} else if (HT[p].weight == 1){	// ����
			HT[p].weight = 2;
			if (HT[p].rchild != 0){
				p = HT[p].rchild;
				cd[cdlen++] = '1';
			}
		} else{						// HT[p].weight == 2���˻�
			HT[p].weight = 0;
			p = HT[p].parent;		// �˵����ڵ㣬���볤�ȼ�1
			--cdlen;
		}
	}// while
}// GetHuffmanCode