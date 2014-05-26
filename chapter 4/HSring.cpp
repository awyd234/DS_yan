#include <stdlib.h>
#include <stdio.h>

#include "HString.h"

Status StrAssign(HString &T, char *chars){
	// 生成一个其值等于串常量chars的串T
	int i;
	char *c;
	if (T.ch) free(T.ch);
	for (i = 0, c = chars; *c; ++i, ++c);
	if (!i){
		T.ch = NULL;
		T.length = 0;
	} else{
		if (!(T.ch = (char *)malloc(i * sizeof(char))))
			exit(OVERFLOW);
		for (int j = 0; j < i; j++)
			T.ch[j] = chars[j];
		T.length = i;
	}
	return OK;
}// StrAssign

Status StrCopy(HString &T, HString S){
	// 若串S存在，由串S复制得串T，并返回OK，否则返回ERROR
	int i = 0;
	if (!S.ch) return ERROR;
	if (T.ch) free(T.ch);
	if (!(T.ch = (char *)malloc(S.length * sizeof(char))))
		exit(OVERFLOW);
	T.length = S.length;
	for (i = 0; i < T.length; i++)
		T.ch[i] = S.ch[i];
	return OK;
}// StrCopy

int StrLength(HString S){
	// 返回S的元素个数，称为串的长度
	return S.length;
}// StrLength

int StrCompare(HString S, HString T){
	// 若S > T，则返回值 > 0，若S = T，则返回值 = 0，若S < T，则返回值 < 0
	int i;
	for (i = 0; i < S.length && i < T.length; ++i)
		if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}// StrCompare

Status ClearString(HString &S){
	// 将S清为空串
	if (S.ch){
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}// ClearString

Status Concat(HString &T, HString S1, HString S2){
	// 用T返回由S1与S2联结而成的新串
	int i;
	if (T.ch) free(T.ch);
	if (!(T.ch = (char *)malloc((S1.length + S2.length)*sizeof(char))))
		exit(OVERFLOW);
	for (i = 0; i < S1.length; i++)
		T.ch[i] = S1.ch[i];
	T.length = S1.length + S2.length;
	for (i = 0; i < S2.length; i++)
		T.ch[i + S1.length] = S2.ch[i];
	return OK;
}// Concat

Status SubString(HString &Sub, HString S, int pos, int len){
	// 用Sub返回串S的第pos个字符起长度为len的子串
	// 其中，1 <= pos <= StrLength(S) 且 0 <= len <= StrLength(S)-pos+1
	if (pos < 1 || pos > StrLength(S) || len < 0 || len > StrLength(S) - pos + 1)
		return ERROR;
	if (Sub.ch) free(Sub.ch);
	if (!len){
		Sub.ch = NULL;
		Sub.length = 0;
	} else{
		Sub.ch = (char *)malloc(len * sizeof(char));
		for (int i = 0; i < len; i++){
			Sub.ch[i] = S.ch[pos - 1 + i];
		}
		Sub.length = len;
	}
	return OK;
}// SubString