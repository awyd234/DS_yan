//顺序栈与队列的宏定义
#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100		//存储空间初始分配量
#define STACKINCREMENT 10		//存储空间分配增量

typedef char SElemType;		//针对不同的要求选择不同类型 char 或 int
typedef int QElemType;
typedef int Status;

#endif