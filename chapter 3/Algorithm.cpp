#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Algorithm.h"
#include "type_def.h"
#include "sq_stack.h"

void conversion(){
	// p48 算法3.1 数制转换
	// 对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数
	SqStack S;
	int N;
	SElemType e;
	InitStack(S);
	scanf("%d",&N);
	while (N){
		Push(S, N%8);
		N = N / 8;
	}
	while (!StackEmpty(S)){
		Pop(S, e);
		printf("%d", e);
	}
}// conversion

Status BracketMatch(char *expr){
	// p49 3.2.2 括号匹配的检验
	// 匹配括号，若出错则返回FALSE，否则返回TRUE
	SqStack S;
	InitStack(S);
	SElemType e;
	int i = 0;
	while (*(expr + i) != '\0'){
		switch (*(expr + i)){
			case '(': Push(S, *(expr + i)); break;
			case '[': Push(S, *(expr + i));  break;
			case ')': {
						  Pop(S, e);
						  if (e != '(') return FALSE;
						  break;
			}
			case ']': {
						  Pop(S, e);
						  if (e != '[') return FALSE;
						  break;
			}
			default: break;
		}
		i++;
	}
	return TRUE;
}// BracketMatch

void LineEdit(){
	// P50 算法3.2 行编辑程序
	// #:退格 @:退行
	// 利用字符栈S，从终端接收一行并传送至调用过程的数据区
	SqStack S;
	InitStack(S);
	SElemType e;
	char ch = getchar();
	while (ch != EOF){
		while (ch != EOF && ch != '\n'){
			switch (ch){
				case'#': 
					Pop(S, e);
					break;
				case'@':
					ClearStack(S);
					break;
				default:
					Push(S, ch);
					break;
			}
			ch = getchar();	//从终端接收下一个字符
		}
		StackTraverse(S, Visit_Display_Char);
		ClearStack(S);
		if (ch != EOF) ch = getchar();
	}
	DestroyStack(S);
}// LineEdit

//算法3.3在另一个工程中

//P52 表达式求职
bool In(char c){
	// 判断是否为操作符，若是则返回TRUE，否则FLASE
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
		return TRUE;
	return FALSE;
}// IsOPTR(char c)
