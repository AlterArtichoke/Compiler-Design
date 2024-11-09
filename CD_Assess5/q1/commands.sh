bison -d three_address.y
lex three_address.l
gcc lex.yy.c three_address.tab.c -o three_address
./three_address