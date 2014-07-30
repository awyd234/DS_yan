#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "MyHeader.h"

//----- 开放定址哈希表存储结构 -----
typedef struct {
	ElemType	*elem;			// 数据元素存储基址，动态分配数组
	int			count;			// 当前数据元素个数
	int			sizeindex;		// hashsize[sizeindex]为当前容量
}HashTable;

#define NULLKEY UINT_MAX
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

Status SearchHash(HashTable &H, KeyType K, int &p, int &c);
int Hash(KeyType K, int p);
Status collision(int &p, int c, int len);
Status InsertHash(HashTable &H, ElemType e);
Status CreateHashTable(HashTable &H, char *filename);
Status RecreateHashTable(HashTable &H);
Status InitHashTable(HashTable &H);
void DisplayHashTable(HashTable H);

#endif