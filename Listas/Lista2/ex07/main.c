#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ehPalindromo(char str[]) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        // Ignorar caracteres não letras
        while (i < j && !isalpha(str[i])) i++;
        while (i < j && !isalpha(str[j])) j--;

        if (i < j && tolower(str[i]) != tolower(str[j]))
            return 0; // não é palíndromo

        i++;
        j--;
    }
    return 1; // é palíndromo
}

int main() {
    char linha[1000];

    while (1) {
        fgets(linha, sizeof(linha), stdin);

        // remover '\n' do final
        linha[strcspn(linha, "\n")] = 0;

        if (strcmp(linha, "FIM") == 0)
            break;

        if (ehPalindromo(linha))
            printf("SIM\n");
        else
            printf("NAO\n");
    }

    return 0;
}
