#ifndef _HSTRING_H_
#define _HSTRING_H_

//---------- 串的堆分配存储表示 ----------
#include "type_def.h"

typedef struct{
	char	*ch;		// 若是非空串，则按串长分配存储区，否则ch为NULL
	int		length;		// 串长度
}HString;

Status StrAssign(HString &T, char *chars);
Status StrCopy(HString &T, HString S);
int StrLength(HString S);
int StrCompare(HString S, HString T);
Status ClearString(HString &S);
Status Concat(HString &T, HString S1, HString S2);
Status SubString(HString &Sub, HString S, int pos, int len);

#endif