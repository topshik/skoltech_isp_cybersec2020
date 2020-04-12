#include <unistd.h>

int main(int argc, char const *argv[]) {
    write(1, "Hi there!\n", 10);
    write(1, "I'm a cool program that tries to write down a flag.\n", 52);
    sleep(3);
    write(1, "Ok, I'm starting...\n", 20);
    sleep(2);
    write(1337, "v3ry_b3utiful_fl4g_yasss", 24);
    write(1, "I dunno if it's ok but i tried to.\n", 35);
    return 0;
}