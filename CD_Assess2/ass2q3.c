#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_LINE_LENGTH 256

const char *keywords[] = {"int", "return", "if", "else", "while", "for", "do", "switch", "case", "default", "break", "continue", "void", "char", "float", "double", "long", "short", "unsigned", "signed", "static", "struct", "union", "enum", "typedef", "const", "sizeof", "volatile", "extern", "register", "auto", "goto", "include", "define", NULL};

int isKeyword(const char *token) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void printOperatorName(char c) {
    printf("Operator, ");
    switch (c) {
        case '+': printf("Addition: %c\n\n", c); break;
        case '-': printf("Subtraction: %c\n\n", c); break;
        case '*': printf("Multiplication: %c\n\n", c); break;
        case '/': printf("Division: %c\n\n", c); break;
        case '=': printf("Assignment: %c\n\n", c); break;
        case '<': printf("Less than: %c\n\n", c); break;
        case '>': printf("Greater than: %c\n\n", c); break;
        case '&': printf("Logical AND: %c\n\n", c); break;
        case '|': printf("Logical OR: %c\n\n", c); break;
        case '!': printf("Logical NOT: %c\n\n", c); break;
        case '^': printf("Bitwise XOR: %c\n\n", c); break;
        case '%': printf("Modulus: %c\n\n", c); break;
        case '(': printf("Left parenthesis: %c\n\n", c); break;
        case ')': printf("Right parenthesis: %c\n\n", c); break;
        case '{': printf("Left curly brace: %c\n\n", c); break;
        case '}': printf("Right curly brace: %c\n\n", c); break;
        case '[': printf("Left square bracket: %c\n\n", c); break;
        case ']': printf("Right square bracket: %c\n\n", c); break;
        case ',': printf("Comma: %c\n\n", c); break;
        case ';': printf("Semicolon: %c\n\n", c); break;
        default: break;
    }
}

void identifyTokens(char *input) {
    char token[MAX_TOKEN_LENGTH];
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {
            while (isalpha(input[i]) || isdigit(input[i]) || input[i] == '_') {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            if (isKeyword(token)) {
                printf("Keyword: %s\n\n", token);
            } else {
                printf("Identifier: %s\n\n", token);
            }
            j = 0;
        }

        else if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Number: %s\n\n", token);
            j = 0;
        }

        else if (strchr("+-*/=<>!&|^%", input[i])) {
            token[j++] = input[i++];
            if ((token[0] == '=' || token[0] == '!' || token[0] == '<' || token[0] == '>') && input[i] == '=') {
                token[j++] = input[i++];
            } else if ((token[0] == '&' || token[0] == '|') && input[i] == token[0]) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Operator: %s\n\n", token);
            printOperatorName(token[0]);
            j = 0;
        }

        else if (strchr("(){}[];,", input[i])) {
            token[j++] = input[i++];
            token[j] = '\0';
            printOperatorName(token[0]);
            j = 0;
        }

        else {
            i++;
        }
    }
}

void identifyTokensFromFile(FILE *file) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        identifyTokens(line);
    }
}

int main() {
    char filename[] = "user_program.txt";
    FILE *file = fopen(filename, "w");

    if (!file) {
        printf("Error: Could not open file for writing.\n");
        return 1;
    }

    printf("Enter a small program (up to 5 lines), end input with a blank line:\n");

    char input[MAX_LINE_LENGTH];
    int lineCount = 0;

    while (fgets(input, sizeof(input), stdin)) {
        if (strcmp(input, "\n") == 0 || lineCount >= 5) {
            break;
        }
        fputs(input, file);
        lineCount++;
    }

    fclose(file);

    // Now open the file for reading and identify tokens
    file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file for reading.\n");
        return 1;
    }
    printf("\n");
    identifyTokensFromFile(file);
    fclose(file);

    return 0;
}
