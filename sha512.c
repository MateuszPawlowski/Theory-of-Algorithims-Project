#include <stdio.h>
#include <inttypes.h>

// Endianess. Adapted from:
//   https://developer.ibm.com/technologies/systems/articles/au-endianc/
#include <byteswap.h>
const int _i = 1;
#define islilend() ((*(char*)&_i) != 0)

// Words and bytes
#define WORD uint64_t
#define PF PRIx64
#define BYTE uint8_t

// Page 5 of the secure hash standard
#define ROTL(_x,_n) ((_x << _n) | (_x >> ((sizeof(_x)*8) - _n)))
#define ROTR(_x,_n) ((_x >> _n) | (_x << ((sizeof(_x)*8) - _n)))
#define SHR(_x,_n) (_x >> _n)

// Page 10 of the secure hash standard
#define CH(_x,_y,_z) ((_x & _y) ^ (~_x & _z))
#define MAJ(_x,_y,_z) ((_x & _y) ^ (_x & _z) ^ (_y & _z))

#define SIG0(_x) (ROTR(_x,2)  ^ ROTR(_x,13) ^ ROTR(_x,22))
#define SIG1(_x) (ROTR(_x,6)  ^ ROTR(_x,11) ^ ROTR(_x,25))
#define Sig0(_x) (ROTR(_x,7)  ^ ROTR(_x,18) ^ SHR(_x,3))
#define Sig1(_x) (ROTR(_x,17) ^ ROTR(_x,19) ^ SHR(_x,10))

// SHA256 works on blocks of 512 bits
union Block {
    // 8 x 64 = 512 - dealing with block as bytes
    BYTE bytes[64];
    // 32 x 16 = 512 - dealing with block as words
    WORD words[16];
    // 64 x 8 = 512 - dealing with the last 64 bits of last block
    uint64_t sixf[8];
};

// For keeping track of where we are with the input message/padding
enum Status {
    READ, PAD, END
};

int sha512(FILE *f, WORD H[]) {
    // The function that performs/orchestrates the SHA256 algorithm on
    // message f

    // The current block
    union Block M;

    // Total number of bits read
    uint64_t nobits = 0;

    // Current status of reading input
    enum Status S = READ;

    // Loop through the (preprocessed) blocks
    //while (next_block(f, &M, &S, &nobits)) {
    //    next_hash(&M, H);
    //}

    return 0;
}

int main(int argc, char *argv[]) {
    // Section 5.3.4
    WORD H[] = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };

    // File pointer for reading
    FILE *f;
    // Open file from command line for reading
    f = fopen(argv[1], "r");

    // Calculate the SHA256 of f
    sha512(f, H);

    // Print the final SHA256 hash
    for (int i = 0; i < 8; i++)
        printf("%08" PF, H[i]);
    printf("\n");

    // Close the file
    fclose(f);

    return 0;
}