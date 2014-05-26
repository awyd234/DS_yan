#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "array.h"

Status InitArray(Array &A, int dim, ...){
	// 若维数dim和随后的各维长度合法，则构造相应的数组A，并返回OK
	int elemtotal, i;
	va_list ap;
	if (dim < 1 || dim > MAX_ARRAY_DIM) return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int));
	if (!A.bounds) exit(OVERFLOW);
	elemtotal = 1;
	va_start(ap, dim);
	for (i = 0; i < dim; ++i){
		A.bounds[i] = va_arg(ap, int);
		if (A.bounds[i] < 0) return ERROR;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if (!A.base) exit(OVERFLOW);
	A.constants = (int *)malloc(dim * sizeof(int));
	if (!A.constants) exit(OVERFLOW);
	A.constants[dim - 1] = 1;
	for (i = dim - 2; i >= 0; --i)
		A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	return OK;
}// InitArray

Status Destroy(Array &A){
	// 销毁数组A
	if (!A.base) return ERROR;
	free(A.base);
	A.base = NULL;
	if (!A.bounds) return ERROR;
	free(A.bounds);
	A.bounds = NULL;
	if (!A.constants) return ERROR;
	free(A.constants);
	A.constants = NULL;
	return OK;
}// Destroy

Status Locate(Array A, va_list ap, int &off){
	// 若ap指示的各下标值合法，则求出该元素在A中相对位置off
	int i, ind;
	off = 0;
	for (i = 0; i < A.dim; ++i){
		ind = va_arg(ap, int);
		if (ind < 0 || ind >= A.bounds[i]) return OVERFLOW;
		off += A.constants[i] * ind;
	}
	return OK;
}// Locate

Status Value(Array A, ElemType &e, ...){
	// A是n维数组，e为元素变量，随后是n个下标值
	// 若各下标不超界，则e赋值为所指定的A的元素的值，并返回OK
	int result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	e = *(A.base + off);
	return OK;
}// Value

Status Assign(Array &A, ElemType e, ...){
	// A是n维数组，e为元素变量，随后是n个下标值
	// 若下标不超界，则将e的值赋给所指定的A的元素，并返回OK
	int result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	*(A.base + off) = e;
	return OK;
}// Assign