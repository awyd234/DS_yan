#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LIST_INIT_SIZE 10
#define FILE_NOT_EXIT -3;	  // 打开文件失败

typedef int Status;
typedef int ElemType;

//----- 对数字型关键字定义 -----
#define EQ(a,b)	((a)==(b))
#define LT(a,b)	((a)<(b))
#define LQ(a,b) ((a)<=(b))

#endif