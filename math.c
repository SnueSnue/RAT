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


int pow(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2 == 1) 
        return base * pow(base, exp - 1);
    else {
        int temp = pow(base, exp / 2);
        return temp * temp;
    }
}

float powf(float base, float exp) {
    return (float)pow((int)base, (int)exp);
}

int is_operator_or_end(char *c) {
    return (*c == '\0' || *c == '+' || *c == '-' || *c == '/' || *c == '*');
}

int find_num(char* str) {
    int i = 0;
    while (str[i] >= '0' && str[i] <= '9' && str[i] != '\n') {
        i++;
    }

    return i;
}

int find_end(char* str){
    /* this function assumes str[0] is an opening parantheses
     * and finds the location of the matching closing parantheses. */
    int i = 0;
    int p_count = 0;
    while (p_count > 0 || i == 0) { 
        if (str[i] == '(') {
            p_count = p_count + 1;
        }
        else if (str[i] == ')') {
            p_count = p_count - 1;
        }
        i++;
    }
    return i-1;
}

void remove_spaces(char *str) {
    char* d = str;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*str++ = *d++);
}

float _calc(char* str, int end){
    /* this function takes a string of math and returns
     * the result of the math from str[0] to str[end] */
    char* num = malloc(100*sizeof(char*));
    int num_len = 0;
    float total_sum = 0.0f;
    float part_sum = 0.0f;
    char last_operator = '+';
    float current_num = 0.0f;

    for (int i = 0; i <= end; i++){
        if ('0' <= str[i] && str[i] <= '9'){
            num[num_len] = str[i];
            num[num_len + 1] = '\0';
            num_len = num_len + 1;
        }
        else {
            char current_char = str[i];
            if (str[i] == '(') {
                if (num_len > 0) {
                    current_char = '*';
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
            else if (str[i] == '*') {
                if (str[i+1] == '*') {
                    int end = find_num(&str[i+2]);
                    current_num = pow(str_to_f(num), _calc(&str[i+2], end));
                    num_len = 0;
                    num[0] = '\0';
                    i = i + end + 2;
                    current_char = str[i];
                }
                else {
                    current_num = str_to_f(num);
                    num_len = 0;
                    num[0] = '\0';
                }
            }
            else {
                current_num = str_to_f(num);
                num_len = 0;
                num[0] = '\0';
            }
            switch (last_operator)
            {
                case '+':
                    part_sum = part_sum + current_num;
                    break;
                case '-':
                    part_sum = part_sum - current_num;
                    break;
                case '*':
                    part_sum = part_sum * current_num;
                    break;
                case '/':
                    part_sum = part_sum / current_num;
                    break;
            }
            if (str[i] == '+' || str[i] == '-' || str[i] == '\0' || str[i] == ')')
            {
                total_sum = total_sum + part_sum;
                part_sum = 0.0f;
            }
            last_operator = current_char;
        }
    }
    return total_sum;
}

float calc(char* str){
    /* this function takes a string of math and returns the result
     * currently, it removes all the spaces from the string, but since
     * the string is printed before this function is called in main.c
     * it is currently not a problem. I might have to add a strcpy later
     * if it becomes a problem.*/
    remove_spaces(str);
    return _calc(str, strlen(str));
}

int gcd(int n, int m){
    /* this function computes the greatest common divisor of two numbers */
    if (n % m == 0){
        return m;
    }

    return gcd(m, n%m);
}
