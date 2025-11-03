#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Programa para calcular Y baseado em X com condições específicas
    int x;
    float y;
    
    scanf("%d", &x);
    
    if (x <= 1) {
        y = 1;
    } 
    else if (x <= 2) {
        y = 2;
    }
    else if (x <= 3) {
        y = x * x;
    }
    else {
        y = x * x * x;
    }
    
    printf("%.2f", y);
    return 0;
}