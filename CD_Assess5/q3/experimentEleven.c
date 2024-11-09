// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// #define MAX_LINE 1000
// #define MAX_TOKENS 4
// #define MAX_VARS 100
// #define MAX_LABEL 50

// typedef struct {
//     char name[50];
//     int offset;
// } Variable;

// Variable symbol_table[MAX_VARS];
// int var_count = 0;
// int temp_var_count = 0;
// int label_count = 0;

// int is_number(const char* str) {
//     if (str[0] == '-' || str[0] == '+') str++;
//     while (*str) {
//         if (!isdigit(*str)) return 0;
//         str++;
//     }
//     return 1;
// }

// int is_conditional(const char* str) {
//     return (str[0] == 'i' && str[1] == 'f');
// }

// int add_variable(const char* name) {
//     for (int i = 0; i < var_count; i++) {
//         if (strcmp(symbol_table[i].name, name) == 0) {
//             return symbol_table[i].offset;
//         }
//     }
//     strcpy(symbol_table[var_count].name, name);
//     symbol_table[var_count].offset = var_count * 2;  
//     var_count++;
//     return (var_count - 1) * 2;
// }

// void generate_load(FILE* output, const char* src, const char* dest) {
//     if (is_number(src)) {
//         fprintf(output, "\tmov ax, %s\n", src);
//     } else {
//         int offset = add_variable(src);
//         fprintf(output, "\tmov ax, [bp-%d]\n", offset);
//     }
// }

// void generate_store(FILE* output, const char* dest) {
//     int offset = add_variable(dest);
//     fprintf(output, "\tmov [bp-%d], ax\n", offset);
// }

// // void process_arithmetic(FILE* output, char* tokens[], int token_count) {
// //     if (token_count != 4) return;

// //     generate_load(output, tokens[2], "ax");

// //     if (strcmp(tokens[3], "") != 0) {  
// //         fprintf(output, "\tpush ax\n");  
// //         generate_load(output, tokens[3], "ax");
// //         fprintf(output, "\tmov bx, ax\n");
// //         fprintf(output, "\tpop ax\n");

// //         if (strchr("+-*/", tokens[1][0])) {
// //             switch (tokens[1][0]) {
// //                 case '+':
// //                     fprintf(output, "\tadd ax, bx\n");
// //                     break;
// //                 case '-':
// //                     fprintf(output, "\tsub ax, bx\n");
// //                     break;
// //                 case '*':
// //                     fprintf(output, "\timul bx\n");  
// //                     break;
// //                 case '/':
// //                     fprintf(output, "\tcwd\n");      
// //                     fprintf(output, "\tidiv bx\n");  
// //                     break;
// //             }
// //         }
// //     }

// //     generate_store(output, tokens[0]);
// // }

// void process_arithmetic(FILE* output, char* tokens[], int token_count) {
//     if (token_count != 4) return;

//     if (strcmp(tokens[1], "*") == 0) {
//         // t1 = c * d
//         generate_load(output, tokens[2], "ax");
//         fprintf(output, "\tmov bx, ax\n");
//         generate_load(output, tokens[3], "ax");
//         fprintf(output, "\timul bx\n");
//         generate_store(output, tokens[0]);
//     } else if (strcmp(tokens[1], "+") == 0) {
//         // t2 = b + t1
//         generate_load(output, tokens[2], "ax");
//         fprintf(output, "\tmov bx, ax\n");
//         generate_load(output, tokens[3], "ax");
//         fprintf(output, "\tadd ax, bx\n");
//         generate_store(output, tokens[0]);
//     } else if (strcmp(tokens[1], "-") == 0) {
//         // t3 = t2 - e
//         generate_load(output, tokens[2], "ax");
//         fprintf(output, "\tmov bx, ax\n");
//         generate_load(output, tokens[3], "ax");
//         fprintf(output, "\tsub ax, bx\n");
//         generate_store(output, tokens[0]);
//     }
// }


// void process_conditional(FILE* output, char* tokens[], int token_count) {
//     if (token_count < 4) return;

//     generate_load(output, tokens[1], "ax");
//     fprintf(output, "\tpush ax\n");
//     generate_load(output, tokens[2], "ax");
//     fprintf(output, "\tmov bx, ax\n");
//     fprintf(output, "\tpop ax\n");
//     fprintf(output, "\tcmp ax, bx\n");

//     char label[MAX_LABEL];
//     strcpy(label, tokens[3]);
//     if (label[strlen(label)-1] == ':') {
//         label[strlen(label)-1] = '\0';
//     }

//     if (strcmp(tokens[0], "if>") == 0) fprintf(output, "\tjg %s\n", label);
//     else if (strcmp(tokens[0], "if<") == 0) fprintf(output, "\tjl %s\n", label);
//     else if (strcmp(tokens[0], "if>=") == 0) fprintf(output, "\tjge %s\n", label);
//     else if (strcmp(tokens[0], "if<=") == 0) fprintf(output, "\tjle %s\n", label);
//     else if (strcmp(tokens[0], "if==") == 0) fprintf(output, "\tje %s\n", label);
//     else if (strcmp(tokens[0], "if!=") == 0) fprintf(output, "\tjne %s\n", label);
// }

// int main() {
//     FILE *input = fopen("input.tac", "r");
//     FILE *output = fopen("output.asm", "w");

//     if (!input || !output) {
//         printf("Error opening files!\n");
//         return 1;
//     }

//     fprintf(output, ".model small\n");
//     fprintf(output, ".stack 100h\n");
//     fprintf(output, ".data\n");
//     fprintf(output, ".code\n");
//     fprintf(output, "main proc\n");
//     fprintf(output, "\tmov ax, @data\n");
//     fprintf(output, "\tmov ds, ax\n");
//     fprintf(output, "\tmov bp, sp\n");
//     fprintf(output, "\tsub sp, 200h\n");  

//     char line[MAX_LINE];
//     char *tokens[MAX_TOKENS];

//     while (fgets(line, MAX_LINE, input)) {
//         if (line[strlen(line)-1] == '\n') {
//             line[strlen(line)-1] = '\0';
//         }

//         if (strlen(line) == 0) continue;

//         if (line[strlen(line)-1] == ':') {
//             fprintf(output, "%s\n", line);
//             continue;
//         }

//         char *token = strtok(line, " ");
//         int token_count = 0;

//         while (token && token_count < MAX_TOKENS) {
//             tokens[token_count++] = token;
//             token = strtok(NULL, " ");
//         }

//         while (token_count < MAX_TOKENS) {
//             tokens[token_count++] = "";
//         }

//         if (is_conditional(tokens[0])) {
//             process_conditional(output, tokens, token_count);
//         } else if (strcmp(tokens[0], "goto") == 0) {
//             fprintf(output, "\tjmp %s\n", tokens[1]);
//         } else {
//             process_arithmetic(output, tokens, token_count);
//         }
//     }

//     fprintf(output, "\tmov ax, 4c00h\n");
//     fprintf(output, "\tint 21h\n");
//     fprintf(output, "main endp\n");
//     fprintf(output, "end main\n");

//     fclose(input);
//     fclose(output);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateAssembly(char *outputFile, FILE *inputFile) {
    FILE *fout = fopen(outputFile, "w");
    if (!fout) {
        perror("Unable to open output file");
        exit(1);
    }

    // Write initial setup for assembly file
    fprintf(fout, "section .data\n");
    fprintf(fout, "a resw 1\n");
    fprintf(fout, "b resw 1\n");
    fprintf(fout, "c resw 1\n");
    fprintf(fout, "d resw 1\n");
    fprintf(fout, "e resw 1\n");
    fprintf(fout, "t1 resw 1\n");
    fprintf(fout, "t2 resw 1\n");
    fprintf(fout, "t3 resw 1\n\n");

    fprintf(fout, "section .text\n");
    fprintf(fout, "global _start\n");
    fprintf(fout, "_start:\n");

    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        char op1[10], op2[10], op3[10];
        if (sscanf(line, "t1 = %s * %s", op1, op2) == 2) {
            // t1 = c * d
            fprintf(fout, "    mov ax, [%s]\n", op1);
            fprintf(fout, "    imul ax, [%s]\n", op2);
            fprintf(fout, "    mov [t1], ax\n");
        } else if (sscanf(line, "t2 = %s + t1", op1) == 1) {
            // t2 = b + t1
            fprintf(fout, "    mov ax, [%s]\n", op1);
            fprintf(fout, "    add ax, [t1]\n");
            fprintf(fout, "    mov [t2], ax\n");
        } else if (sscanf(line, "t3 = t2 - %s", op1) == 1) {
            // t3 = t2 - e
            fprintf(fout, "    mov ax, [t2]\n");
            fprintf(fout, "    sub ax, [%s]\n", op1);
            fprintf(fout, "    mov [t3], ax\n");
        } else if (strcmp(line, "a = t3\n") == 0) {
            // a = t3
            fprintf(fout, "    mov ax, [t3]\n");
            fprintf(fout, "    mov [a], ax\n");
        }
    }

    // Exit code for 8086
    fprintf(fout, "\n    mov ax, 1 ; exit syscall number\n");
    fprintf(fout, "    int 0x80\n");

    fclose(fout);
}

int main() {
    FILE *inputFile = fopen("input.tac", "r");
    if (!inputFile) {
        perror("Error opening .tac file");
        return 1;
    }

    generateAssembly("output.asm", inputFile);
    fclose(inputFile);

    printf("Assembly code has been generated in output.asm\n");
    return 0;
}
