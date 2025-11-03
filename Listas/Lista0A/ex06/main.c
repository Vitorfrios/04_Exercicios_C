#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Ler a razão e o primeiro termo de uma PA e mostrar o seu decimo termo.
    int r,num,pa;
    scanf("%d%d",&r,&num);

    pa = num+((9)*r);
    printf("%d",pa);

    return 0;
}
