#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

#define LH	+1		// ���
#define EH	0		// �ȸ�
#define RH	-1		// �Ҹ�

//----- ���������������Ͷ��� -----
typedef BiTree BSTree;
typedef BiTNode BSTNode;

BiTree SearchBST(BiTree T, KeyType key);
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p);
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);
void R_Rotate(BSTree &p);
void L_Rotata(BSTree &p);
Status InsertAVL(BSTree &T, ElemType e, Boolean &taller);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);

//----- B-�� -----
#define m 3				// B-���Ľף�����Ϊ3
#define RECORD_MAX_SIZE 100			// ��¼���ַ������ֵ

typedef char Record[RECORD_MAX_SIZE];

typedef struct BTNode{
	int				keynum;			// ����йؼ��ֵĸ����������Ĵ�С
	struct BTNode	*parent;		// ָ��˫�׽��
	KeyType			key[m + 1];		// �ؼ���������0�ŵ�Ԫδ��
	struct BTNode	*ptr[m + 1];	// ����ָ������
	Record			*recptr[m + 1];	// ��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;					// B-������B-��������

typedef struct{	
	BTNode	*p;						// ָ���ҵ��Ľ��
	int		i;						// 1...m�ڽ���йؼ��ֵ����
	int		tag;					// 1�����ҳ� ����0������ʧ��
}Result;

Result SearchBTree(BTree T, KeyType K);
int Search(BTree T, KeyType K);
Status InsertBTree(BTree &T, KeyType K);
Status Insert(BTree q, int i, KeyType x, BTree ap);
Status split(BTree q, int s, BTree &ap);
Status NewRoot(BTree &T, BTree q, KeyType x, BTree ap);
Status CreateBTree(BTree &T, char *filename);
void DisplayBTree(BTree T);

#endif