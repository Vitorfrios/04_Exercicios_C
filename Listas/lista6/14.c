#include <stdio.h>
#include <string.h>

void trocar(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permutar(char *str, int inicio, int fim) {
    if (inicio == fim) {
        printf("%s ", str);
    } else {
        for (int i = inicio; i <= fim; i++) {
            trocar((str + inicio), (str + i));
            permutar(str, inicio + 1, fim);
            trocar((str + inicio), (str + i));
        }
    }
}

int main() {
    char string[100];
    
    scanf("%s", string);
    
    int n = strlen(string);
    permutar(string, 0, n - 1);
    printf("\n");
    
    return 0;
}