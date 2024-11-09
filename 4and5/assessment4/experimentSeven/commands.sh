# commands.sh
bison -d calculator.y            # Generates calculator.tab.c and calculator.tab.h
lex calculator.l                 # Processes the lexer file and generates lex.yy.c
gcc lex.yy.c calculator.tab.c -o calculator -lm   # Compiles the output
./calculator                     # Runs the calculator program
