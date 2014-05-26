#include <stdlib.h>
#include <stdio.h>

#include "algorithm.h"
#include "HString.h"

/**
*	串的模式匹配算法 -- KMP算法
*/

int Index_KMP(HString S, HString T, int pos){
	// 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
	// T非空，1 <= pos <= StrLength(S)
	int i = pos, j = 1;
	int next[10000] = {0};
	//get_next(T, next);
	get_nextval(T, next);
	while (i <= StrLength(S) && j <= StrLength(T)){
		if (j == 0 || S.ch[i-1] == T.ch[j-1]){
			++i;
			++j;
		} else{
			j = next[j-1];
		}// if
	}// while
	if (j >= StrLength(T))
		return i - StrLength(T);
	else
		return 0;
}// Index_KMP

void get_next(HString T, int next[]){
	// 求模式串T的next函数值并存入到数组next
	int i = 1, j = 0;
	next[0] = 0;
	while (i < StrLength(T)){
		if (j == 0 || T.ch[i-1] == T.ch[j-1]){
			++i;
			++j;
			next[i-1] = j;
		} else{
			j = next[j-1];
		}// if
	}// while
}// get_next

void get_nextval(HString T, int nextval[]){
	// 求模式串T的next函数修正值并存入到数组nextval
	int i = 1, j = 0;
	nextval[0] = 0;
	while (i < StrLength(T)){
		if (j == 0 || T.ch[i - 1] == T.ch[j - 1]){
			++i;
			++j;
			if (T.ch[i - 1] != T.ch[j - 1]) nextval[i - 1] = j;
			else nextval[i - 1] = nextval[j - 1];
		} else{
			j = nextval[j - 1];
		}// if
	}// while
}// get_nextval