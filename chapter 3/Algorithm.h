//------------第三章中算法与应用------------
#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "type_def.h"

typedef int OperandType;

void conversion();
Status BracketMatch(char *expr);
void LineEdit();
bool In(char c);
char Precede(char c1, char c2);
int Operate(int a, char oper, int b);
int EvaluateExpression();
void mov(char x, int n, char z);
void hanoi(int n, char x, char y, char z);
#endif