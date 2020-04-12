#include <string.h>
#include <stdio.h>

void modif(char *p) {
    for (size_t i = 0; i < strlen(p) - 1; ++i) {
        p[i] += 1;
    }
}

int main(int argc, char const *argv[])
{
    char buf[256];

    if (argc < 2) {
        printf("Usage: %s <STRING>\n", argv[0]);
        return 1;
    }

    strncpy(buf, argv[1], sizeof(buf));
    modif(buf);
    printf("After: %s\n", buf);
    return 0;
}
