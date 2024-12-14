#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define EQ_LEN 50

enum Type {
    eq,
    integer,
    parEnd,
    add,
    sub,
    mult,
    divi,
    parStart,
};


struct Token {
    enum Type type;
    int value;
    struct Token *parent;
    struct Token *op1;
    struct Token *op2;
};

struct Equation {
    char *index;
    struct Token *first;
    struct Token *prev;
    char string[EQ_LEN];
};

int toint(char c) {
    return c - '0';
}

struct Token *find_swap_partner(enum Type operator, struct Token *prev) {
    while (operator < prev->type) {
        prev = prev->parent;
    }
    return prev;
}

struct Token *find_start_par(struct Token *prev) {
    while (prev->type != '(') {
        prev = prev->parent;
    }
    return prev;
}

int get_token(struct Equation *equation) {
    // returns 1, if one token is created
    // returns 0, if no token is created (EOF)
    while (*(equation->index) == ' ' || *(equation->index) == '\n') {
        equation->index++;
    }
    if (*(equation->index) == '\0') {
        return 0;
    }

    // printf("%c\n", *(equation->index));

    struct Token *token_p = (struct Token *)malloc(sizeof(struct Token));

    if (isdigit(*(equation->index))) {
        token_p->type = integer;
        token_p->value = 0;
        while (isdigit(*(equation->index))) {
            token_p->value = token_p->value * 10;
            token_p->value = token_p->value + toint(*equation->index);
            equation->index++;
        }
        equation->prev->op2 = token_p;
        token_p->parent = equation->prev;
        // printf("number %d\n", token_p->value);
    }
    else {
        printf("%c\n", *(equation->index));
        switch (*(equation->index)) {
            case '+': token_p->type = add; break;
            case '-': token_p->type = sub; break;
            case '*': token_p->type = mult; break;
            case '/': token_p->type = divi; break;
            case '(': token_p->type = parStart; break;
            case ')': token_p->type = parEnd; break;
            default: printf("error: unknown operator '%c'\n", *(equation->index)); break;
        }
        if (*(equation->index) == '(') {
            equation->prev->op2 = token_p;
            token_p->parent = equation->prev;
            equation->prev = token_p;
        } else if (*(equation->index) == ')') {
            equation->prev = find_start_par(equation->prev);
            equation->prev->type = parEnd;

        } else {
            struct Token *swap_partner = find_swap_partner(token_p->type, equation->prev);
            token_p->op1 = swap_partner->op2;
            token_p->parent = swap_partner;
            swap_partner->op2 = token_p;
            equation->prev = token_p;
        }
        (equation->index)++;
    }


    return 1;
}

int get_value(struct Token *token_p) {
    int value;
    switch (token_p->type) {
        case integer: value = token_p->value; break;
        case add: value = get_value(token_p->op1) + get_value(token_p->op2); break;
        case sub: value = get_value(token_p->op1) - get_value(token_p->op2); break;
        case mult: value = get_value(token_p->op1) * get_value(token_p->op2); break;
        case divi: value = get_value(token_p->op1) / get_value(token_p->op2); break;
        case parEnd: value = get_value(token_p->op2); break;
        case eq: value = get_value(token_p->op2); break;
        default: printf("parse error on type %c\n", token_p->type); break;
    }
    free(token_p);
    return value;
}

int init_equation(struct Equation *equ, char *str) {
    struct Token *fst = (struct Token *)malloc(sizeof(struct Token));
    fst->type = eq;

    strcpy(equ->string, str);
    equ->index = equ->string;
    equ->first= fst;
    equ->prev = equ->first;

}

int print_equation(struct Token *token_p) {
    switch (token_p->type) {
        case integer: printf("%d", token_p->value); break;
        case add: printf("("); print_equation(token_p->op1); printf("+"); print_equation(token_p->op2); printf(")"); break;
        case sub: printf("("); print_equation(token_p->op1); printf("-"); print_equation(token_p->op2); printf(")"); break;
        case mult: printf("("); print_equation(token_p->op1); printf("*"); print_equation(token_p->op2); printf(")"); break;
        case divi: printf("("); print_equation(token_p->op1); printf("/"); print_equation(token_p->op2); printf(")"); break;
        case eq: printf("="); print_equation(token_p->op2); printf("\n"); break;
        // case sub: value = get_value(token_p->op1) - get_value(token_p->op2); break;
        // case mult: value = get_value(token_p->op1) * get_value(token_p->op2); break;
        // case divi: value = get_value(token_p->op1) / get_value(token_p->op2); break;
        // case eq: value = get_value(token_p->op2); break;
    }
    return 0;
}

int solve(char *equation) {
    // printf("%s\n", equation);
    struct Equation equ;
    init_equation(&equ, equation);
    while (get_token(&equ));
    // print_equation(equ.first);
    return get_value(equ.first);
}

