#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

bool checksum(const std::string &string) {
    if (string.length() != 28) {
        return false;
    }
    int res = 0;
    for (size_t i = 9; i != string.length() - 1; ++i) {
        res += std::pow(string[i], 2);
    }
    if (res == 208317) {
        return true;
    }
    return false;
}

bool validate_flag(const std::string &string) {
    if (!checksum(string)) {
        printf("%s\n", "L0000000s333333r");
        return false;
    }
    for (size_t i = 9; i != string.length() - 3; ++i) {
        if (i % 2 == 1) {
            if (string[i] + 2 != string[i + 2]) {
                printf("%c%s\n", string[i], "L0000000s333333r");
                return false;

            }
        } else {
            if (string[i] - 1 != string[i + 2]) {
                printf("%s\n", "L0000000s333333r");
                return false;

            }
        }
    }
    printf("%s\n", "You win!1!!1!!!!!");
    return true;

}

int main() {
    std::string string;
    getline(std::cin, string);
    bool validate = validate_flag(string);
    return 0;
}

