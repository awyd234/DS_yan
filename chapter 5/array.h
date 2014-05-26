#ifndef _ARRAY_H_
#define _ARRAY_H_

//---------- 数组的顺序存储表示 ----------
#include "type_def.h"

#define MAX_ARRAY_DIM 8
typedef struct{
	ElemType	*base;
	int			dim;
	int			*bounds;
	int			*constants;
}Array;

Status InitArray(Array &A, int dim, ...);
Status Destroy(Array &A);
Status Locate(Array A, va_list ap, int &off);
Status Value(Array A, ElemType &e, ...);
Status Assign(Array &A, ElemType e, ...);

#endif