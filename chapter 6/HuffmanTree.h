//----- �շ������ͺշ�������Ĵ洢��ʾ -----
#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;			// ��̬��������洢�շ�����
typedef char **HuffmanCode;	// ��̬��������洢�շ��������

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int *n);
void Select(HuffmanTree &HT, int n, int &s1, int &s2);
void GetHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n);

#endif