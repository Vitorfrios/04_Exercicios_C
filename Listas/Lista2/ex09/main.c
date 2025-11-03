#include <stdio.h>
#include <stdlib.h>

int main()
{
/*Um comerciante deseja fazer o levantamento do lucro das mercadorias que ele comercializa.
Para isto, mandou digitar uma linha para cada mercadoria com o preço de compra e de venda de cada uma.
A última linha contém preço de compra igual a 0.
Escreva um programa que:
    a) Determine e escreva quantas mercadorias proporcionaram:
        • Lucro < 10%
        • 10% <= lucro <= 20%
        • Lucro > 20%
    b) Determine e escreva o valor total de compra e de venda de todas as   mercadorias, assim como o lucro total.*/

    float Pc=-1,Pv,Compra=0,Venda=0,Lucro=0,L=0;
    int Lm10=0,Lentre=0,Lsup=0;
    while(Pc != 0){
        scanf("%f%f",&Pc,&Pv);
        Lucro += Pv-Pc;
        L=((Pv/Pc)-1)*100;
        Venda += Pv;
        Compra += Pc;
        if(L<10)Lm10++;
        else if(L>=10 && L<=20)Lentre++;
        else if(L>20) Lsup++;

    }

    printf("%d\n", Lm10);
    printf("%d\n", Lentre);
    printf("%d\n", Lsup);
    printf("%.2f\n", Compra);
    printf("%.2f\n", Venda);
    printf("%.2f\n", Lucro);
    return 0;
}
