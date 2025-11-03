#include <stdio.h>

int mdc(int n, int b) {
    if (b == 0)
        return n;               // caso base
    else
        return mdc(b, n % b);   // recursão
}

int main() {
    int n, b;
    scanf("%d %d", &n, &b);

    printf("%d\n", mdc(n, b));

    return 0;
}
