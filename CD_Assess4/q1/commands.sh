bison -d infixToPostfix.y
lex infixToPostfix.l
gcc lex.yy.c infixToPostfix.tab.c -o infixToPostfix
./infixToPostfix