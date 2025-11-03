#include <stdio.h>
#include <stdlib.h>

int pote(int a, int b) {
    if (b == 0)
        return 1;           // qualquer número elevado a 0 é 1
    else
        return a * pote(a, b - 1);
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", pote(a, b));
    return 0;
}
