bison -d mat2.y
lex mat2.l
gcc -std=c99 -Wall mat2.tab.c lex.yy.c -o mat2
./mat2
