#ifndef _STATIC_SEARCH_H_
#define _STATIC_SEARCH_H_

typedef BiTree SOSTree;		// ���Ų��������ö�������Ĵ洢�ṹ

//----- ��̬���ұ��˳��洢�ṹ -----

typedef struct{
	ElemType	*elem;		// ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int			length;		// ����
}SSTable;

Status CreateTable(SSTable &ST, int n, char *filename);
void Destroy(SSTable &ST);
int Search_Seq(SSTable ST, KeyType key);
int Search_Bin(SSTable ST, KeyType key);
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high);
void FindSW(ElemType R[], float sw[], int length);
Status CreateSOSTree(SOSTree &T, SSTable ST);

#endif