#include <stdio.h>

void bin_print(unsigned int i){
    // Number of bits in an integer
    int j = sizeof(unsigned int) * 8;

    // Temporary variable
    int k;

    // Loop over the number of bits in i
    for (j--; j >= 0; j--){
        // 
        k = ((1 << j) & i) ? 1 : 0;
        // Print k
        printf("%d", k);
    }
}

// Standard main signature
int main(int argc, char *argv[]){
    
    // Set i to a literal value
    unsigned int i = 0xffffffff;

    // What we're printing
    printf("Original:  ");
    // Print i in binary
    bin_print(i);
    // End line
    printf("\t%xt%u\n", i, i);

    for (int j = 0; j < 40; j++){
        // What the operation is
        printf("%3u << %2d: ", i, j);
        // i shifted left j times
        bin_print(i << j);
        // End line
        printf("\n");
    }

    // Everything is okay
    return 0;
}
 