%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token 'a' 'b'

%%
start: 'a' 'b' repeat_bbaa 'b' 'b' 'a' repeat_ba
     ;

repeat_bbaa: /* epsilon */
           | repeat_bbaa 'b' 'b' 'a' 'a'
           ;

repeat_ba: /* epsilon */
         | repeat_ba 'b' 'a'
         ;

%%

int main() {
    printf("Enter a string: ");
    if (yyparse() == 0) {
        printf("Accepted!\n");
    } else {
        printf("Rejected!\n");
    }
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}