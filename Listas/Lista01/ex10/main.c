#include <stdio.h>

int main() {
    int vel_max, vel_motor, excesso;

    //printf("Digite a velocidade maxima permitida: ");
    scanf("%d", &vel_max);

   //printf("Digite a velocidade do motorista: ");
    scanf("%d", &vel_motor);

    if (vel_motor <= vel_max) {
        printf("Motorista respeitou a lei\n");
    } else {
        excesso = vel_motor - vel_max;

        if (excesso <= 10)
            printf("Multa de 50 reais\n");
        else if (excesso <= 30)
            printf("Multa de 100 reais\n");
        else
            printf("Multa de 200 reais\n");
    }

    return 0;
}
