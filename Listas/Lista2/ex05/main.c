#include <stdio.h>
#include <stdlib.h>

int main()
{
/*A prefeitura de uma cidade fez uma pesquisa entre seus habitantes, coletando dados sobre o salário e número de filhos de cada habitante.
A prefeitura deseja saber:
    a) média do salário da população; media do salario/habtantes
    b) média do número de filhos;
    c) maior salário;
    d) percentual de pessoas com salário até R$100,00.
    O final da leitura de dados se dará com a entrada de um salário negativo. */

    float sal=0,Maior_sal=0,Media_sal=0;
    int filhos,media_f=0,Hab=0,percent=0;

    while(sal >= 0) {
        scanf("%f", &sal);
        if(sal >= 0) {      // só processa se for salário válido
            scanf("%d", &filhos);

            if(sal > Maior_sal) Maior_sal = sal;
            Media_sal += sal;
            media_f += filhos;
            Hab++;

            if(sal <= 100) percent++;  // para o percentual
        }
    }
    printf("%.2f\n", Media_sal / Hab);
    printf("%d\n", media_f / Hab);
    printf("%.2f\n", Maior_sal);
    printf("%.2f\n", (float)percent / Hab * 100);

    return 0;
}
