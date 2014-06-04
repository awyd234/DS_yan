//----- 赫夫曼树和赫夫曼编码的存储表示 -----
#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;			// 动态分配数组存储赫夫曼树
typedef char **HuffmanCode;	// 动态分配数组存储赫夫曼编码表

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int *n);
void Select(HuffmanTree &HT, int n, int &s1, int &s2);
void GetHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n);

#endif