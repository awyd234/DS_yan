/*
    problem 1.19
    Requirement: �Ա�д�㷨����i!*2^i(i=0,1,...,n-1)��ֵ����������a[arrize]
                 �ĸ��������У�����������������������ֵΪMAXINT����
                 n>arrize���ĳ��k(0<=k<=n-1)ʹk!*2^k>MAXINTʱ��Ӧ��������
                 ע��ѡ������Ϊ�Ϻõĳ���������
    MAXINT�ĵó�������-1��signedתunsigned
*/
#include <stdio.h>
#define arrize 40
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

int main()
{
    int i, pow2=1, jci=1, n, judge = 0;
    int a[arrize];
    unsigned MAXINT = -1;
    printf("Please input the number n: ");
    scanf("%d",&n);
    if(n > arrize){
        printf("The number n is over arrize!\n");
        return FALSE;
    }
    for(i=0; i<=n; i++)
    {
        if(judge){
            printf("\nThe calculation overflow when i=%d!\n",i);
            return FALSE;
        }
        if(i%5==0&&i) printf("\n");
        if(i==0){
            pow2 *= 2;
            a[i] = jci * pow2;
            printf("%d\t",a[i]);
            continue;
        } else{
            pow2 *= 2;
            jci *= i;
            a[i] = jci * pow2;
        }
        if(a[i] > MAXINT/(2*i+2) ){
            judge = 1;
        }
        printf("%d\t",a[i]);
    }
    return TRUE;
}
