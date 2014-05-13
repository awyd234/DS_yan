#include <stdlib.h>
#include <stdio.h>
#include "LinkList.h"

int main()
{
    LinkList La;
    ElemType e;
    printf("Assigment for La:\n");
    CreateList_L(La,5);
    printf("The elements in La:\n");
    Print_L(La);
    ListDelete_L(La, 2, e);
    printf("We have deleted the 2th element in La:\n");
    Print_L(La);
    ListInsert_L(La, 2, e);
    printf("Put the element deleted in the proier statement in 2th:\n");
    Print_L(La);
    LinkList Lb;
    printf("Assigment for another LinkList Lb:\n");
    CreateList_L(Lb,5);
    printf("The elements in Lb:\n");
    Print_L(Lb);
    LinkList Lc;
    MergeList_L(La, Lb, Lc);
    printf("After merging La and Lb:\n");
    Print_L(Lc);
    return 0;
}
