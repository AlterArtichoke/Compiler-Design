bison -d mat1.y
lex mat1.l
gcc lex.yy.c mat1.tab.c -o mat1
./mat1