yacc -d three_address.y
lex three_address.l
gcc lex.yy.c y.tab.c -o three_address
./three_address