// Rudimentary Arithmetic Tool

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++){
        printf("%s ", argv[i]);
    }

    if (argc == 1){
        char input[100];
        fgets(input, 100, stdin);
        for (int i = 0; input[i] != '\0'; i++){
            if (input[i] == '\n'){
                input[i] = '\0';
            }
        }
        printf("%s = %.4g\n", input, calc(input));
        return 0;
    }

    if (argc == 2){
        printf("= %.4g\n", calc(argv[1]));
        return 0;
    }

    switch (argv[1][0])
    {
        case 'g':
            printf("= %d\n", gcd(str_to_int(argv[2]), str_to_int(argv[3])));
            break;

        default:
            printf("= rat error\n");
    }

    return 0;
}
