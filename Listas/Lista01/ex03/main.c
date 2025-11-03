#include <stdio.h>

int main() {
    int ano_nascimento, idade;
    char resposta;

    // Lê ano de nascimento
    scanf("%d", &ano_nascimento);
    // Lê se a pessoa dirige (S ou N)
    scanf(" %c", &resposta); // espaço ignora o \n

    if (resposta == 'N' || resposta == 'n') {
        printf("Nao pode dirigir\n");
        idade = 2025 - ano_nascimento - 1;
    } else {
        idade = 2025 - ano_nascimento;
        printf(idade >= 18 ? "Pode dirigir\n" : "Nao pode dirigir\n");
    }

    printf("%d\n", idade);

    return 0;
}
