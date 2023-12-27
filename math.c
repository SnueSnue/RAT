// Rudimentary Arithmetic Tool

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int str_to_int(char* str){
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++){
        num = num * 10 + (str[i] - 48);
    }

    return num;
}

float str_to_f(char* str){
    return (float)str_to_int(str);
}

float calc(char* input){
    char* str = malloc(100*sizeof(char*));
    strcpy(str, input);

    char plus = '+';
    strncat(str, &plus, 1);

    char* num = malloc(100*sizeof(char*));
    int num_len = 0;
    float total_sum = 0.0f;
    float token_sum = 0.0f;
    char last_operator = '+';

    for (int i = 0; i < strlen(str); i++){
        if ('0' <= str[i] && str[i] <= '9'){
            num[num_len] = str[i];
            num[num_len + 1] = '\0';
            num_len = num_len + 1;
            //strncat(num, &str[i], 1);
        }
        else {
            switch (last_operator)
            {
                case '+':
                    token_sum = token_sum + str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                    break;
                case '-':
                    token_sum = token_sum - str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                    break;
                case '*':
                    token_sum = token_sum * str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                    break;
                case '/':
                    token_sum = token_sum / str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                    break;
            }
            if (str[i] == '+' || str[i] == '-')
            {
                total_sum = total_sum + token_sum;
                token_sum = 0.0f;
            }
            last_operator = str[i];
        }
    }

    return total_sum;
}

int gcd(int n, int m){
    if (n % m == 0){
        return m;
    }

    return gcd(m, n%m);
}
