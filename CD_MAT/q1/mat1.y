%{
#include <stdio.h>
#include <stdlib.h>

// Declare the variables defined in the Lex code
int count_a = 0;
int count_b = 0;

extern int yylex(void); // Scanner function

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
%}

%token NEWLINE

%%

input:
    /* empty */ 
    | input line
;

line:
    NEWLINE {
        if (count_a != count_b) {
            printf("Accepted: a^%d b^%d (m != n)\n", count_a, count_b);
        } else {
            printf("Not Accepted: a^%d b^%d (m == n)\n", count_a, count_b);
        }
        count_a = 0;
        count_b = 0;
    }
;

%%

int main() {
    printf("Enter a sequence of a's followed by b's:\n");
    yyparse();
    return 0;
}
