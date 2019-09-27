#include <stdio.h>
#include "crc.h"

int main() {
    const char *answer = build_answer("112233445573\0", "00308300087104\0");
    printf("answer: %s\n", answer);

    return 0;
}