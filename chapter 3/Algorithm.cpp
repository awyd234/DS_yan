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

//P52 ���ʽ��ְ
bool In(char c){
	// �ж��Ƿ�Ϊ�������������򷵻�TRUE������FLASE
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
		return TRUE;
	return FALSE;
}// IsOPTR(char c)
