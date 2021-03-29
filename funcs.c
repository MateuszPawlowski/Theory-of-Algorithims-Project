#include <stdio.h>
#include <inttypes.h>

#define WORD uint32_t
#define PF PRIX32

#define CH(x,y,z)  (x&y)^(~x&z)
#define MAJ(x,y,z) (x&y)^(x&z)^(y&z)

int main(int argc, char *argv[]) {

    uint32_t x = 0xf0f0f0f0;
    uint32_t y = 0x0f0f0f0f;
    uint32_t z = 0xf0f0f0f0;

    WORD ans;

    ans = CH(x, y, z);
    printf("Ch(%08" PF ",%08" PF ",%08" PF ")=%08" PF "\n", x, y, z, ans);

    ans = MAJ(x, y, z);
    printf("Maj(%08" PF ",%08" PF ",%08" PF ")=%08" PF "\n", x, y, z, ans);

    return 0;
}