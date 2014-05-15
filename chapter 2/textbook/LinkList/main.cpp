#include <stdlib.h>
#include <stdio.h>
#include "LinkList.h"

int main()
{
    LinkList La;
    InitList_L(La);
    ElemType e;
    printf("Assigment for La:\n");
    CreateList_L(La,5);
    printf("The elements in La:\n");
    ListTraverse_L(La,Display_L);
    ListDelete_L(La, 2, e);
    printf("We have deleted the 2th element in La:\n");
    ListTraverse_L(La,Display_L);
    ListInsert_L(La, 2, e);
    printf("Put the element deleted in the proier statement in 2th:\n");
    ListTraverse_L(La,Display_L);
    LinkList Lb;
    InitList_L(Lb);
    printf("Assigment for another LinkList Lb:\n");
    CreateList_L(Lb,5);
    printf("The elements in Lb:\n");
    ListTraverse_L(Lb,Display_L);
    LinkList Lc;
    InitList_L(Lc);
    MergeList_L(La, Lb, Lc);
    printf("After merging La and Lb:\n");
    ListTraverse_L(Lc,Display_L);
    printf("The number of elements in Lb: %d\n",ListLength_L(Lc));
    Destroy_L(La);
    Destroy_L(Lb);
    Destroy_L(Lc);
    return 0;
}
