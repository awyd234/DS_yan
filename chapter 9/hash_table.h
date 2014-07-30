#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "MyHeader.h"

//----- ���Ŷ�ַ��ϣ��洢�ṹ -----
typedef struct {
	ElemType	*elem;			// ����Ԫ�ش洢��ַ����̬��������
	int			count;			// ��ǰ����Ԫ�ظ���
	int			sizeindex;		// hashsize[sizeindex]Ϊ��ǰ����
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