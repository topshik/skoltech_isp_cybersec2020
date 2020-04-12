#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win() {
    printf("%s\n", "You win!\n");
}

void loose() {
    printf("%s\n", "You loose!\n");
}

int main(int argc, char **argv) {
    char flag[256];

    if (argc < 2) {
        printf("Usage: %s <STRING>\n", argv[0]);
        return 1;
    }

    strncpy(&flag, argv[1], 256);
    if (!strcmp(flag, "h4ck_7h3_wh0le_w0r1d_1337")) {
        win();
    } else {
        loose();
    }
    return 0;
}
