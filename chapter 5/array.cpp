#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "array.h"

Status InitArray(Array &A, int dim, ...){
	// ��ά��dim�����ĸ�ά���ȺϷ���������Ӧ������A��������OK
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
	// ��������A
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
	// ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�����λ��off
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
	// A��nά���飬eΪԪ�ر����������n���±�ֵ
	// �����±겻���磬��e��ֵΪ��ָ����A��Ԫ�ص�ֵ��������OK
	int result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	e = *(A.base + off);
	return OK;
}// Value

Status Assign(Array &A, ElemType e, ...){
	// A��nά���飬eΪԪ�ر����������n���±�ֵ
	// ���±겻���磬��e��ֵ������ָ����A��Ԫ�أ�������OK
	int result, off;
	va_list ap;
	va_start(ap, e);
	if ((result = Locate(A, ap, off)) <= 0) return result;
	*(A.base + off) = e;
	return OK;
}// Assign