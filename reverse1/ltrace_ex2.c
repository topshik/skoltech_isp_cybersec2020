#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char flag[256];
    printf("%s", "enter flag:\n");
    scanf("%s", flag);
    long long k = 0;
    int r;
    while (++k != 1e7) {
        r = rand();
    }

    if (!strcmp(flag, "s0me_1337_fl4g")) {
        printf("%s\n", "You win!");
    } else {
        printf("%s\n", "Nope!");
    }
    return 0;
}
