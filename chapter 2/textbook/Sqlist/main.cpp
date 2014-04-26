#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

int main()
{
    SqList La,Lb,Lc;
    ElemType e;
    InitList_Sq(La);
    InitList_Sq(Lb);
    InitList_Sq(Lc);
    ListInsert_Sq(La,1,1);
    ListInsert_Sq(La,2,3);
    ListInsert_Sq(La,3,5);
    ListInsert_Sq(La,4,7);
    ListInsert_Sq(La,5,9);
    ListInsert_Sq(Lb,1,2);
    ListInsert_Sq(Lb,2,6);
    ListInsert_Sq(Lb,3,8);
    ListInsert_Sq(Lb,4,12);
    printf("La:\n");
    ListTraverse_Sq(La,display_Sq);
    printf("\nLb:\n");
    ListTraverse_Sq(Lb,display_Sq);
    Merge_Sq(La,Lb,Lc);
    printf("\nLc:\n");
    ListTraverse_Sq(Lc,display_Sq);
    ListDelete_Sq(Lc,4,e);
    printf("\nAfter deleting the 4th element in Lc:\n");
    ListTraverse_Sq(Lc,display_Sq);
    printf("\nThe 4th element in the old Lc was: %d\n",e);
    printf("After clearing La, the following line will be blank:\n");
    ClearList_Sq(La);
    ListTraverse_Sq(La,display_Sq);
    DestroyList_Sq(La);
    DestroyList_Sq(Lb);
    DestroyList_Sq(Lc);
    printf("\nThe Lc has been destroyed, so there will be an error!\n");
    printf("\nThat's all about the implements of Sqlist!\n");
    ListTraverse_Sq(Lc,display_Sq);//Lc已销毁，此处会出错
    return 0;
}
