#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Algorithm.h"
#include "type_def.h"
#include "sq_stack.h"

void conversion(){
	// p48 �㷨3.1 ����ת��
	// �������������һ���Ǹ�ʮ������������ӡ��������ֵ�İ˽�����
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
	// p49 3.2.2 ����ƥ��ļ���
	// ƥ�����ţ��������򷵻�FALSE�����򷵻�TRUE
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
	// P50 �㷨3.2 �б༭����
	// #:�˸� @:����
	// �����ַ�ջS�����ն˽���һ�в����������ù��̵�������
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
			ch = getchar();	//���ն˽�����һ���ַ�
		}
		StackTraverse(S, Visit_Display_Char);
		ClearStack(S);
		if (ch != EOF) ch = getchar();
	}
	DestroyStack(S);
}// LineEdit

//�㷨3.3����һ��������

/*
	P52 ���ʽ��ֵ
*/

bool In(char c){
	// �ж��Ƿ�Ϊ�������������򷵻�TRUE������FLASE
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
		return TRUE;
	return FALSE;
}// In

char Precede(char c1, char c2){
	// �Ƚ������c1��c2�����ȼ���������ʽΪ'>','=',��'<'
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
	// ��a��b���������oper������
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
	// P53 �㷨3.4
	// �������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ���������
	SqStack OPTR, OPND;
	InitStack(OPTR);
	bool judgePre=0;	// �ж������ǰһ���ַ��Ƿ�Ϊ���֣����ڶ�λ��������
	Push(OPTR, '#');
	InitStack(OPND);
	int c, x, medi;
	OperandType theta;
	int a, b;
	c = getchar();
	while (c!='#' || GetTop(OPTR)!='#'){
		if (!In(c)){	//������������ջ
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
	�㷨3.5 n��hanoi����
*/

int count = 0;

void mov(char x, int n, char z){
	printf("%d.Move disk %i from  %c  to  %c\n", ++count, n, x, z);
}

void hanoi(int n, char x, char y, char z){
	// ������x�ϰ�ֱ����С���������϶��±��Ϊ1��n��n��Բ�̰�����ᵽ����z��
	// y������������
	// �ᶯ���� mov(x,n,z) �ɶ���Ϊ��count�ǳ�ֵΪ0��ȫ�ֱ������԰ᶯ������
	// printf("%i.Move disk %i from  %c  to  %c\n", ++count,n,x,z);
	if (n == 1){
		mov(x, 1, z);
	} else{
		hanoi(n - 1, x, z, y);
		mov(x, n, z);
		hanoi(n - 1, y, x, z);
	}
}