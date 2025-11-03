#include <stdio.h>

int main() {
    float diaria_normal;
    
    // Lê o valor normal da diária
    scanf("%f", &diaria_normal);
    
    // Calcula a diária promocional (25% de desconto)
    float diaria_promocional = diaria_normal * 0.75;
    
    // Número total de apartamentos
    int total_apartamentos = 75;
    
    // Cálculo da ocupação (arredondando para inteiro)
    int ocupacao_normal = (int)(total_apartamentos * 0.5 + 0.5);
    int ocupacao_promocional = (int)(total_apartamentos * 0.8 + 0.5);
    
    // Cálculo dos valores totais arrecadados
    float total_normal = ocupacao_normal * diaria_normal;
    float total_promocional = ocupacao_promocional * diaria_promocional;
    float diferenca = total_promocional - total_normal;
    
    // Imprime os resultados
    printf("Valor promocional: %.2f\n", diaria_promocional);
    printf("Promocional com 80%% ocupado: %.2f\n", total_promocional);
    printf("Normal com 50%% ocupado: %.2f\n", total_normal);
    printf("Diferença  entre os valores: %.2f\n", diferenca);
    
    return 0;
}