#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_LINE_LENGTH 256

// List of keywords
const char *keywords[] = {"int", "return", "if", "else", "while", "for", "do", "switch", "case", "default", "break", "continue", "void", "char", "float", "double", "long", "short", "unsigned", "signed", "static", "struct", "union", "enum", "typedef", "const", "sizeof", "volatile", "extern", "register", "auto", "goto", "include", "define", NULL};

// Function to check if a token is a keyword
int isKeyword(const char *token) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to print names with their symbols
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
        // Skip whitespaces
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // If the character is an alphabet or underscore (part of an identifier or keyword)
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

        // If the character is a digit (part of a number)
        else if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Number: %s\n\n", token);
            j = 0;
        }

        // If the character is an
        else if (strchr("+-*/=<>!&|^%", input[i])) {
            token[j++] = input[i++];
            // Check for multi-characters like '==', '!=', '<=', '>='
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

        // If the character is a special symbol (like ;, (), {}, etc.)
        else if (strchr("(){}[];,", input[i])) {
            token[j++] = input[i++];
            token[j] = '\0';
            printOperatorName(token[0]);
            j = 0;
        }

        // For unrecognized characters, just skip them
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
    FILE *file = fopen("input_program.txt", "r");
    if (!file) {
        printf("Error: Could not open file.\n\n");
        return 1;
    }

    identifyTokensFromFile(file);
    fclose(file);
    return 0;
}
