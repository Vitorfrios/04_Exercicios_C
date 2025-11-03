#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    //Ler a razão e o primeiro termo de uma PG e mostrar o seu quinto termo.


    int r,num,pg;
    scanf("%d%d",&r,&num);
    pg = num*pow(r,4);
    printf("%d",pg);

    return 0;
}
