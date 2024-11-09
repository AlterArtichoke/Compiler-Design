yacc -d pattern.y
lex pattern.l
gcc lex.yy.c y.tab.c -o pattern
./pattern