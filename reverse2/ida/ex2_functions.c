#include <stdio.h>

void say_it(const char *s) {
    printf("%s\n", s);
}


int main (int argc, char **argv) {
    say_it(argv[1]);
    return 0;
}
