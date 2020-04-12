#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char flag[256];
    printf("%s", "enter a long flag:\n");
    scanf("%s", flag);

    char *to = (char*) malloc(6);
    const int margin = 5;
    const int flag_length = 19;
    strncpy(to, flag + flag_length + margin, 12);
    printf("%s\n", to);

    if (!strncmp(flag, "Y0ur_v3ry_l0ng_fl4g", flag_length)) {
        if (!strcmp(to, "_i5_g00d_n0w")) {
            printf("%s\n", "You win!");
        } else {
            printf("%s\n", "Nope!");
        }
    } else {
        printf("%s\n", "Nope!");
    }
    return 0;
}
