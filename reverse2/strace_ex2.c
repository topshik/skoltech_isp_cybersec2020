#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    char *flag = "FLAG_y0u_g07_m3";
    int kek;
    for (int i = 0; i != strlen(flag); ++i) {
        char next_dir[i + 2];
        strncpy(next_dir, flag, i + 1);
        next_dir[i + 1] = '\0';

        kek = chdir(next_dir);
        if (kek) {
            printf("%s\n", "Whooops, can't find directory!\n");
            break;
        }
        chdir("../");
    }
    return 0;
}
