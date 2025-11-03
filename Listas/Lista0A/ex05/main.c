#include <stdio.h>
#include <math.h>

int main() {
    float ladoA, ladoB, hipo;
    scanf("%f %f", &ladoA, &ladoB);

    hipo = sqrt(pow(ladoA, 2) + pow(ladoB, 2));

    printf("Hipotenusa: %.2f\n", hipo);
    return 0;
}
