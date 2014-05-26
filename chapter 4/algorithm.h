#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "HString.h"

int Index_KMP(HString S, HString T, int pos);
void get_next(HString S, int next[]);
void get_nextval(HString T, int nextval[]);

#endif