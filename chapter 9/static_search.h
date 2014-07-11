#ifndef _STATIC_SEARCH_H_
#define _STATIC_SEARCH_H_

typedef BiTree SOSTree;		// 次优查找树采用二叉链表的存储结构

//----- 静态查找表的顺序存储结构 -----

typedef struct{
	ElemType	*elem;		// 数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	int			length;		// 表长度
}SSTable;

Status CreateTable(SSTable &ST, int n, char *filename);
void Destroy(SSTable &ST);
int Search_Seq(SSTable ST, KeyType key);
int Search_Bin(SSTable ST, KeyType key);
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high);
void FindSW(ElemType R[], float sw[], int length);
Status CreateSOSTree(SOSTree &T, SSTable ST);

#endif