#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymath.h"
#define BUF_SIZE 50


char equation[BUF_SIZE];

int main() {
    equation[read(0, equation, BUF_SIZE-1)-1] = '\0';
    // read(0, equation, BUF_SIZE);
    // printf("%d\n", solve(equation));
    printf("%s = %d\n", equation, solve(equation));
    return 0;
}
