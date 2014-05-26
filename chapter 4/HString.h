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
Status StrEmpty(HString S);
int StrLength(HString S);
int StrCompare(HString S, HString T);
Status ClearString(HString &S);
Status Concat(HString &T, HString S1, HString S2);
Status SubString(HString &Sub, HString S, int pos, int len);
int Index(HString S, HString T, int pos);
Status Replace(HString &S, HString T, HString V);
Status StrInsert(HString &S, int pos, HString T);
Status StrDelete(HString &S, int pos, int len);
Status Destroy(HString &S);

#endif