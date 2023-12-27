// Rudimentary Arithmetic Tool

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int str_to_int(char* str){
    /* this function is used to convert the user input string to an integer */
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++){
        num = num * 10 + (str[i] - 48);
    }

    return num;
}

float str_to_f(char* str){
    /* this converts a string containing an integer to a float */
    return (float)str_to_int(str);
}

int find_end(char* str){
    /* this function assumes str[0] is an opening parantheses
     * and finds the location of the matching closing parantheses. */
    int i = 0;
    int p_count = 1;
    while (p_count > 0) {
        i++;
        if (str[i] == '(') {
            p_count = p_count + 1;
        }
        else if (str[i] == ')') {
            p_count = p_count - 1;
        }
    }
    return i;
}

float _calc(char* str, int end){
    /* this function takes a string of math and returns
     * the result of the math from str[0] to str[end] */
    char* num = malloc(100*sizeof(char*));
    int num_len = 0;
    float total_sum = 0.0f;
    float token_sum = 0.0f;
    char last_operator = '+';
    float current_num = 0.0f;

    for (int i = 0; i <= end; i++){
        if ('0' <= str[i] && str[i] <= '9'){
            num[num_len] = str[i];
            num[num_len + 1] = '\0';
            num_len = num_len + 1;
        }
        else {
            if (str[i] != '(') {
                current_num = str_to_f(num);
                num_len = 0;
                num[0] = '\0';
            }
            else {
                if (num_len > 0) {
                    str[i-1] = '*';
                    i = i - 1;
                    current_num = str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                }
                else {
                    int end = find_end(&str[i]);
                    current_num = _calc(&str[i]+1, end);
                    i = i + end;
                }
            }
            switch (last_operator)
            {
                case '+':
                    token_sum = token_sum + current_num;
                    break;
                case '-':
                    token_sum = token_sum - current_num;
                    break;
                case '*':
                    token_sum = token_sum * current_num;
                    break;
                case '/':
                    token_sum = token_sum / current_num;
                    break;
            }
            if (str[i] == '+' || str[i] == '-' || str[i] == '\0' || str[i] == ')')
            {
                total_sum = total_sum + token_sum;
                token_sum = 0.0f;
            }
            last_operator = str[i];
        }
    }
    return total_sum;
}

float calc(char* str){
    /* this function takes a string of math and returns the result */
    return _calc(str, strlen(str));
}

int gcd(int n, int m){
    /* this function computes the greatest common divisor of two numbers */
    if (n % m == 0){
        return m;
    }

    return gcd(m, n%m);
}
