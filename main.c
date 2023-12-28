// Rudimentary Arithmetic Tool

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>

#include "math.h"

const char *argp_program_version = "RAT 0.1";
const char *argp_program_bug_address = "<snue@proton.me>";
static char doc[] = "Rudimentary Arithmetic Tool designed for writing math in Kakoune.\nReads a statement from stdin and outputs the full equation, including the solution.";
static char args_doc[] = "[MATH...]";

static struct argp_option options[] = {
    { "discard", 'd', 0, 0, "Discard input text."},
};

struct arguments
{
    //char *args[1];
    int discard;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'd':
            arguments->discard = 1;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char* argv[])
{
    struct arguments arguments;

    arguments.discard = 0;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    char input[100];
    fgets(input, 100, stdin);
    for (int i = 0; input[i] != '\0'; i++){
        if (input[i] == '\n'){
            input[i] = '\0';
        }
    }
    
    if (arguments.discard == 0)
        printf("%s = ", input);
    printf("%.4g\n", calc(input));
    return 0;
}
