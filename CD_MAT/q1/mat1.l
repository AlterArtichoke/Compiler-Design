%{
#include <stdio.h>
#include "mat1.tab.h" // Updated to match generated parser header

extern int count_a; // Define global variables here
extern int count_b;

%}

%x A B FINAL INVALID

%%

<INITIAL>^a+          { count_a = yyleng; BEGIN(A); }
<INITIAL>^b+          { count_b = yyleng; BEGIN(B); }
<INITIAL>[^ab\n]      { BEGIN(INVALID); }
<INITIAL>\n           { return NEWLINE; }

<A>a+                 { count_a += yyleng; }
<A>b+                 { count_b = yyleng; BEGIN(FINAL); }
<A>[^ab\n]            { BEGIN(INVALID); }
<A>\n                 { return NEWLINE; }

<B>b+                 { count_b += yyleng; }
<B>a+                 { count_a = yyleng; BEGIN(FINAL); }
<B>[^ab\n]            { BEGIN(INVALID); }
<B>\n                 { return NEWLINE; }

<FINAL>\n             { return NEWLINE; }
<FINAL>[^ab\n]        { BEGIN(INVALID); }

<INVALID>[^\n]        ; 
<INVALID>\n           { printf("Not Accepted\n"); BEGIN(INITIAL); count_a = count_b = 0; }

%%

int yywrap() {
    return 1;
}
