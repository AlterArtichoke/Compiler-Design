%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*
NUMBER      {DIGIT}+(\.{DIGIT}+)?(E[-+]?{DIGIT}+)?
WHITESPACE  [ \t\n]+
OPERATOR    [\+\-\*/=<>!]
PAREN       [\(\)\{\}\[\]]

%%

"if"        { printf("Keyword: if\n"); }
"else"      { printf("Keyword: else\n"); }
"while"     { printf("Keyword: while\n"); }
"return"    { printf("Keyword: return\n"); }

{ID}        { printf("Identifier: %s\n", yytext); }
{NUMBER}    { printf("Number: %s\n", yytext); }
{OPERATOR}  { printf("Operator: %s\n", yytext); }
{PAREN}     { printf("Brackets: %s\n", yytext); }
{WHITESPACE}    { /* Ignore whitespace */ }

.           { printf("Special character: %s\n", yytext); }

%%

int main() {    
    FILE *file = fopen("input_program.txt", "r");
        if(!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
        yylex();
        fclose(file);
        return 0;
}

int yywrap() {
    return 1;
}
