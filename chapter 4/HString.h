#ifndef _HSTRING_H_
#define _HSTRING_H_

//---------- ���Ķѷ���洢��ʾ ----------
#include "type_def.h"

typedef struct{
	char	*ch;		// ���Ƿǿմ����򰴴�������洢��������chΪNULL
	int		length;		// ������
}HString;

Status StrAssign(HString &T, char *chars);
Status StrCopy(HString &T, HString S);
int StrLength(HString S);
int StrCompare(HString S, HString T);
Status ClearString(HString &S);
Status Concat(HString &T, HString S1, HString S2);
Status SubString(HString &Sub, HString S, int pos, int len);

#endif