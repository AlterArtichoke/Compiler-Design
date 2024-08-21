#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_LINE_LENGTH 256

void identifyTokens(char *input) {
    char token[MAX_TOKEN_LENGTH];
    int i = 0, j = 0;

    while (input[i] != '\0') {
        // Skip whitespaces
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // If the character is an alphabet or underscore (part of an identifier)
        if (isalpha(input[i]) || input[i] == '_') {
            while (isalpha(input[i]) || isdigit(input[i]) || input[i] == '_') {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Identifier: %s\n", token);
            j = 0;
        }

        // If the character is a digit (part of a number)
        else if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printf("Number: %s\n", token);
            j = 0;
        }

        // If the character is an operator
        else if (strchr("+-*/=", input[i])) {
            token[j++] = input[i++];
            token[j] = '\0';
            printf("Operator: %s\n", token);
            j = 0;
        }

        // If the character is a special symbol (like ;, (), etc.)
        else if (strchr(";(),{}", input[i])) {
            token[j++] = input[i++];
            token[j] = '\0';
            printf("Special Symbol: %s\n", token);
            j = 0;
        }

        // Move to next character
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
