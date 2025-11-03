#include <stdio.h>
#include <stdlib.h>

int main()
{
//Ler um valor de hora (e minuto), calcular e mostrar quantos minutos se passaram desde o início do dia.
    int h,m;
    scanf("%d%d",&h,&m);
    printf("%d",h*60+m);
    return 0;
}
