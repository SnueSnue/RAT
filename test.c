#include <stdio.h>
#include <string.h>

#include "math.h"


int main(int argc, char* argv[]) {
    int error_count = 0;

    char test_string[100];
    int ans;

    strcpy(test_string, "2+3");
    ans = 5;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    strcpy(test_string, "2*3");
    ans = 6;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    strcpy(test_string, "3**3+1");
    ans = 28;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    strcpy(test_string, "1+3**2");
    ans = 10;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    strcpy(test_string, "2+5(1+4)");
    ans = 27;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    strcpy(test_string, "2**(1+2)");
    ans = 8;
    if (calc(test_string) != ans) {
        printf("%s = expected %d, got %g\n",test_string, ans, calc(test_string));
        error_count = error_count + 1;
    }

    if (error_count == 0)
        printf("all tests passed sucessfully :))\n");
    else {
        printf("%d error(s)\n", error_count);
    }
}
