//
// Created by Artem Botnev on 26/09/2019.
//

#include "crc.h"

int main() {
    const char *answer = build_answer("112233445573\0", "00308300087104\0");
    printf("answer: %s\n", answer);

    return 0;
}