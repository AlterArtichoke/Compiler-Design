yacc -d infixToPostfix.y
lex infixToPostfix.l
gcc lex.yy.c y.tab.c -o infixToPostfix
./infixToPostfix