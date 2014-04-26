/*
    problem 1.20
    Requirement: 编写算法求一元多项式E(i=0->n)(ai*x^i)的值Pn(x0)
                 选择你认为最好的输入输出方法
                 input:     ai(i=0,i,...,n),x0,n
                 output:    Pn(x0)
    Notice: 不要对多项式的每一项求x的幂
    ;
*/
#include <stdio.h>
int sumPn(int a[], int x, int n)
{
    int i=0, Pn=0, powx=1;
    for(i=0; i <= n; i++)
    {
        Pn += a[i]*powx;
        powx *= x;
    }
    return Pn;
}

int main()
{
    int n, a[1000]={0}, i, x;
    printf("Please input the number n: ");
    scanf("%d",&n);
    printf("Please input the number x: ");
    scanf("%d",&x);
    printf("Please input the array a[%d]: ",n+1);
    for(i=0; i<=n; i++) scanf("%d",&a[i]);
    printf("a0*%d^0 +...+ a%d*x^%d = %d",x,n+1,n+1,sumPn(a,x,n));
    return 0;
}
