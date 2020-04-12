#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char login[256];
    char password[256];
    printf("%s", "enter login:\n");
    scanf("%s", login);
    printf("%s", "enter password:\n");
    scanf("%s", password);
    if (!strcmp(login, "s3cr3t_us3r")) {
        if (!strcmp(password, "my_v3ry_s3cur3_p4sswd")) {
            printf("%s\n", "You win!");
        }
    } else {
        printf("%s\n", "You l00se :-(");
    }

    return 0;
}
