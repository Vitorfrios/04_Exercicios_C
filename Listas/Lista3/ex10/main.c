#include <stdio.h>

char categoriaNadador(int idade) {
    if (idade >= 5 && idade <= 7)
        return 'F';
    else if (idade >= 8 && idade <= 10)
        return 'E';
    else if (idade >= 11 && idade <= 13)
        return 'D';
    else if (idade >= 14 && idade <= 15)
        return 'C';
    else if (idade >= 16 && idade <= 17)
        return 'B';
    else return 'A';

}

int main() {
    int n; // número de nadadores
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int idade;
        scanf("%d", &idade);
        char cat = categoriaNadador(idade);
        printf("%c\n", cat); // imprime a categoria do nadador i
    }

    return 0;
}
