#include <stdio.h>
#include <stdlib.h>

int main()
{

/*Em uma eleição presidencial existem quatro candidatos. Os votos são informados através de códigos.
Os dados utilizados para a contagem dos votos obedecem à seguinte codificação:
    • 1,2,3,4 = voto para os respectivos candidatos;
    • 5 = voto nulo;
    ° 6 = voto em branco;
Elabore um algoritmo que leia o código do candidato em um voto.
Calcule e escreva:
    • total de votos para cada candidato;
    • total de votos nulos;
    • total de votos em branco.
    Como finalizador do conjunto de votos, tem-se o valor 0.

*/
    int Voto=-1,voto1 = 0, voto2 = 0, voto3 = 0, voto4 = 0;
    int votoNulo = 0;
    int votoBranco = 0;

    while(Voto!=0){
        scanf("%d",&Voto);

        switch (Voto) {
            case 1: voto1++; break;
            case 2: voto2++; break;
            case 3: voto3++; break;
            case 4: voto4++; break;
            case 5: votoNulo++; break;
            case 6: votoBranco++; break;
            default:
                break;
        }
    }

    printf("%d\n", voto1);
    printf("%d\n", voto2);
    printf("%d\n", voto3);
    printf("%d\n", voto4);
    printf("%d\n", votoNulo);
    printf("%d\n", votoBranco);

    return 0;
}
