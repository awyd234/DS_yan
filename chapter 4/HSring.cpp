#include <stdlib.h>
#include <stdio.h>

#include "HString.h"

Status StrAssign(HString &T, char *chars){
	// ����һ����ֵ���ڴ�����chars�Ĵ�T
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
	// ����S���ڣ��ɴ�S���Ƶô�T��������OK�����򷵻�ERROR
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

Status StrEmpty(HString S){
	// ��SΪ�մ����򷵻�TRUE�����򷵻�FALSE
	if (!S.ch)
		return ERROR;
	if (S.length == 0){
		return TRUE;
	} else{
		return FALSE;
	}
}// StrEmpty

int StrLength(HString S){
	// ����S��Ԫ�ظ�������Ϊ���ĳ���
	return S.length;
}// StrLength

int StrCompare(HString S, HString T){
	// ��S > T���򷵻�ֵ > 0����S = T���򷵻�ֵ = 0����S < T���򷵻�ֵ < 0
	int i;
	for (i = 0; i < S.length && i < T.length; ++i)
		if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
	return S.length - T.length;
}// StrCompare

Status ClearString(HString &S){
	// ��S��Ϊ�մ�
	if (S.ch){
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}// ClearString

Status Concat(HString &T, HString S1, HString S2){
	// ��T������S1��S2������ɵ��´�
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
	// ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
	// ���У�1 <= pos <= StrLength(S) �� 0 <= len <= StrLength(S)-pos+1
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

int Index(HString S, HString T, int pos){
	// ��S��T���ڣ�TΪ�ǿմ���1 <= pos <= StrLength(S)
	// ������S�д��ںʹ�Tֵ��ͬ��ֵ���򷵻���������S�е�pos���ַ�֮���һ�γ��ֵ�
	// λ�ã����򷵻�0
	int n, m, i;
	HString sub;
	if (pos < 1 || pos > StrLength(S)) return ERROR;
	if (pos > 0){
		n = StrLength(S);
		m = StrLength(T);
		i = pos;
		while (i <= n - m + 1){
			SubString(sub, S, i, m);
			if (StrCompare(sub, T) != 0){
				++i;
			} else{
				return i;
			}
		}// while
	}// if
	return 0;
}// Index

Status Replace(HString &S, HString T, HString V){
	// ��S��T��V���ڣ�T�ǿ�
	// ��V�������S�д��ֵ�������T��ȵĲ��ص����Ӵ�
	int n, i=1;
	HString Sub;
	Sub.ch = NULL;
	if (!S.ch || !V.ch || !T.ch || !T.length)
		return ERROR;
	n = T.length;
	while (i <= S.length){
		if (!(SubString(Sub, S, i, n))){
			break;
		}
		if (StrCompare(T, Sub)){
			i++;
			continue;
		}
		StrDelete(S, i, n);
		StrInsert(S, i, V);
		i += StrLength(V) - n;
	}
	return OK;
}// Replace

Status StrInsert(HString &S, int pos, HString T){
	// ��S��T���ڣ�1 <= pos <= StrLength(S)+1
	// �ڴ�S�ĵ�pos���ַ�ǰ���봮T
	if (pos < 1 || pos >StrLength(S) + 1)
		return ERROR;
	HString SubFront, SubRear, Temp;
	SubFront.ch = SubRear.ch = Temp.ch = NULL;
	SubString(SubFront, S, 1, pos - 1);
	SubString(SubRear, S, pos, StrLength(S) - pos + 1);
	Concat(Temp, SubFront, T);
	Concat(S, Temp, SubRear);
	return OK;
}// StrInsert

Status StrDelete(HString &S, int pos, int len){
	// ��S���ڣ�1 <= pos <= StrLength(S)-len+1
	// �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	if (pos < 1 || pos > StrLength(S) - len + 1)
		return ERROR;
	HString Sub, T;
	Sub.ch = T.ch = NULL;
	SubString(Sub, S, 1, pos - 1);
	Sub.length = pos - 1;
	SubString(T, S, pos + len , StrLength(S) - len - pos +1);
	T.length = StrLength(S) - len - pos + 1;
	Concat(S, Sub, T);
	return OK;
}// StrDelete

Status Destroy(HString &S){
	// ����S
	if (!S.ch) return ERROR;
	free(S.ch);
	return OK;
}// Destroy