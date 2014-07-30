#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

#define LH	+1		// 左高
#define EH	0		// 等高
#define RH	-1		// 右高

//----- 二叉排序树的类型定义 -----
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

//----- B-树 -----
#define m 3				// B-树的阶，暂设为3
#define RECORD_MAX_SIZE 100			// 记录中字符的最大值

typedef char Record[RECORD_MAX_SIZE];

typedef struct BTNode{
	int				keynum;			// 结点中关键字的个数，即结点的大小
	struct BTNode	*parent;		// 指向双亲结点
	KeyType			key[m + 1];		// 关键字向量，0号单元未用
	struct BTNode	*ptr[m + 1];	// 子树指针向量
	Record			*recptr[m + 1];	// 记录指针向量，0号单元未用
}BTNode, *BTree;					// B-树结点和B-树的类型

typedef struct{	
	BTNode	*p;						// 指向找到的结点
	int		i;						// 1...m在结点中关键字的序号
	int		tag;					// 1：查找成 功，0：查找失败
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