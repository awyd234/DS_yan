#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MyHeader.h"

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	// w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC。
	int m, i, s1, s2, start, c, f;
	char *cd;
	HuffmanTree p;
	if (n <= 1) return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) *sizeof(HTNode));	// 0号单元未用
	for (p = HT, i = 1; i <= n; ++i, ++p, ++w)
		*p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		*p = { 0, 0, 0, 0 };
	for (i = n + 1; i < m; ++i){
		// 在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1，和s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//----- 从叶子到根逆向求每个字符的赫夫曼编码 -----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));		// 分配n个字符编码的头指针向量
	cd = (char *)malloc(n * sizeof(char));			// 分配求编码的工作空间
	cd[n - 1] = '\0';								// 编辑结束符
	for (i = 1; i <= n; ++i){						// 这个字符求赫夫曼编码
		start = n - 1;								// 编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent){	// 从叶子到根逆向求编码
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));	// 为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);				// 从cd复制编码（串）到HC
	}
	free(cd);					// 释放工作空间
}// HuffmanCoding

void Select(HuffmanTree &HT, int n, int &s1, int &s2){
	// 在HT[1...n]选择parent为0且weight最小的两个结点，其序号分别为s1，和s2
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
	//无栈非递归遍历赫夫曼树，求赫夫曼编码
	int m, p, cdlen, i;
	char *cd;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	cd = (char *)malloc(n*sizeof(char));
	m = 2 * n - 1;
	p = m;
	cdlen = 0;
	for (i = 1; i <= m; ++i)		// 遍历赫夫曼树时用做结点状态标志
		HT[i].weight = 0;
	while (p){
		if (HT[p].weight == 0){		// 向左
			HT[p].weight = 1;
			if (HT[p].lchild != 0){
				p = HT[p].lchild;
				cd[cdlen++] = '0';
			} else if (HT[p].rchild == 2){		// 登记叶子结点的字符的编码
				HC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[p], cd);		// 复制编码（串）
			}
		} else if (HT[p].weight == 1){	// 向右
			HT[p].weight = 2;
			if (HT[p].rchild != 0){
				p = HT[p].rchild;
				cd[cdlen++] = '1';
			}
		} else{						// HT[p].weight == 2，退回
			HT[p].weight = 0;
			p = HT[p].parent;		// 退到父节点，编码长度减1
			--cdlen;
		}
	}// while
}// GetHuffmanCode