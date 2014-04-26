/*
    problem 1.16
    Requirement: 自大至小依次输出顺序读入的三个整数X,Y,Z
    没用tmp，直接通过相加来交换，这样不利在于易溢出，也可用位操作交换。
*/
#include <stdio.h>
void Descending()
{
    int X, Y, Z;
    scanf("%d %d %d",&X,&Y,&Z);
    if(X < Y){
        X = X + Y;Y = X - Y;X = X - Y;
        }
    if(Y < Z){
        Y = Y + Z; Z = Y - Z; Y = Y - Z;
        if(X < Y){
            X = X + Y;
            Y = X - Y;
            X = X - Y;
            }
        }
    printf("%d > %d > %d",X,Y,Z);
}

int main()
{
    Descending();
    return 0;
}
