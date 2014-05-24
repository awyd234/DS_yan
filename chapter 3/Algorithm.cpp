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

/*
	P52 表达式求值
*/

bool In(char c){
	// 判断是否为操作符，若是则返回TRUE，否则FLASE
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
		return TRUE;
	return FALSE;
}// In

char Precede(char c1, char c2){
	// 比较运算符c1与c2的优先级，返回形式为'>','=',或'<'
	switch (c1){
		case '+':
		case '-':
			switch (c2){
				case '+':
				case '-':
				case ')':
				case '#':
					return '>';
					break;
				case '*':
				case '/':
				case '(':
					return '<';
					break;
				default:
					break;
			}
			break;
		case '*':
		case '/':
			switch (c2){
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
				case '#':
					return '>';
					break;
				case '(':
					return '<';
					break;
				default:
					break;
			}
			break;
		case '(':
			switch (c2){
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
					return '<';
					break;
				case ')':
					return '=';
					break;
				default:
					break;
			}
			break;
		case ')':
			switch (c2)
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
				case '#':
					return '>';
					break;
				default:
					break;
			}
			break;
		case '#':
			switch (c2)
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
					return '<';
					break;
				case '#':
					return '=';
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}// Precede

int Operate(int a, char theta, int b){
	// 对a与b进行运算符oper的运算
	switch (theta)
	{
		case '+':
			return a + b;
			break;
		case '-':
			return a - b;
			break;
		case '*':
			return a * b;
			break;
		case '/':
			return a / b;
			break;
		default:
			break;
	}
	return ERROR;
}// int Operate

int EvaluateExpression(){
	// P53 算法3.4
	// 算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合
	SqStack OPTR, OPND;
	InitStack(OPTR);
	bool judgePre=0;	// 判断输入的前一个字符是否为数字，用于多位数的运算
	Push(OPTR, '#');
	InitStack(OPND);
	int c, x, medi;
	OperandType theta;
	int a, b;
	c = getchar();
	while (c!='#' || GetTop(OPTR)!='#'){
		if (!In(c)){	//不是运算符则进栈
			c = c - '0';
			if (!In(GetTop(OPND)) && judgePre){
				Pop(OPND, medi);
				c += medi * 10;
			}
			Push(OPND, c);
			judgePre = 1;
			c = getchar();
		} else {
			switch (Precede(GetTop(OPTR),c)){
				case '<':
					Push(OPTR, c); 
					c = getchar();
					break;
				case '=':
					Pop(OPTR, x);
					c = getchar();
					break;
				case '>':
					Pop(OPTR, theta);
					Pop(OPND, b);
					Pop(OPND, a);
					Push(OPND, Operate(a, theta, b));
					break;
				default:
					break;
			}
			judgePre = 0;
		}
		
	}
	return GetTop(OPND);
}// EvaluateExpression

/*
	算法3.5 n阶hanoi问题
*/

int count = 0;

void mov(char x, int n, char z){
	printf("%d.Move disk %i from  %c  to  %c\n", ++count, n, x, z);
}

void hanoi(int n, char x, char y, char z){
	// 将塔座x上按直径由小到大且自上而下编号为1至n的n个圆盘按规则搬到塔座z上
	// y可作辅助塔座
	// 搬动操作 mov(x,n,z) 可定义为（count是初值为0的全局变量，对搬动计数）
	// printf("%i.Move disk %i from  %c  to  %c\n", ++count,n,x,z);
	if (n == 1){
		mov(x, 1, z);
	} else{
		hanoi(n - 1, x, z, y);
		mov(x, n, z);
		hanoi(n - 1, y, x, z);
	}
}