%{
#include "mat2.tab.h"  // Include the token definitions from Yacc
%}

%%
a    return 'a';
b    return 'b';
.    return yytext[0];  // Catch-all for invalid characters
%%

int yywrap(){
    return 1;
}