yacc -d counter.y
lex counter.l
gcc lex.yy.c y.tab.c -o counter -lfl
./counter