/*
    problem 1.16
    Requirement: �Դ���С�������˳��������������X,Y,Z
    û��tmp��ֱ��ͨ��������������������������������Ҳ����λ����������
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
