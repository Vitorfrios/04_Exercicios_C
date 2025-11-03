#include <stdio.h>

int main() {
    char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = alfabeto;
    
    while(*ptr != '\0') {
        printf("%c ", *ptr);
        ptr++;
    }
    printf("\n");
    
    return 0;
}