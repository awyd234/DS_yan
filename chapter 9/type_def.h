#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define FILE_NOT_EXIT -3;	  // 打开文件失败
#define STACK_INIT_SIZE 100   // 栈初始化值
#define STACKINCREMENT 10     // 栈容量每次增加的值
#define DATA_SIZE	20		  // 表中数据内容的大小


typedef int Status;
typedef bool Boolean;

typedef int KeyType;

typedef struct{
	KeyType	key;			// 关键字
	char data[DATA_SIZE];	// 数据内容
	int weight;				// 权值
}ElemType;

//----- 对数字型关键字定义 -----
#define EQ(a,b)	((a)==(b))
#define LT(a,b)	((a)<(b))
#define LQ(a,b) ((a)<=(b))

#endif