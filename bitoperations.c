#include <stdio.h>

int main(int argc, char *argv[]){
    
    int i = 0xF1; // 11110001

    printf("Dec: %d\n", i);
    printf("Hex: %X\n", i);

    printf("Size of int: %d\n", sizeof(i));
    printf("Size of int: %d\n", sizeof(int));
    printf("Size of int: %d\n", sizeof(char));

    char c = 41;
    printf("C in char is: %c\n", c);
    printf("C in int is: %d\n", c);

    int j = 1000000000;
    printf("J in char is: %d\n", j);
    printf("J in int is: %c\n", (char) j);
    printf("J int from char is: %d\n", (int) (char) j);

    
    return 0;
}
 