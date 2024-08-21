#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26
#define MAX_STATE_NAME_LENGTH 20
#define MAX_SYMBOL_NAME_LENGTH 5

// Structure to represent DFA
typedef struct {
    int transition[MAX_STATES][MAX_SYMBOLS]; // Transition table
    int numStates; // Number of states
    char stateNames[MAX_STATES][MAX_STATE_NAME_LENGTH]; // State names
    char symbols[MAX_SYMBOLS][MAX_SYMBOL_NAME_LENGTH]; // Symbol names
    int numSymbols; // Number of symbols
    int startState; // Start state index
    int acceptStates[MAX_STATES]; // Accept states
} DFA;

// Function to initialize DFA
void initializeDFA(DFA *dfa) {
    memset(dfa->transition, -1, sizeof(dfa->transition)); // Initialize all transitions to -1
    memset(dfa->acceptStates, 0, sizeof(dfa->acceptStates)); // Initialize all accept states to 0 (not accepting)
}

// Function to find the index of a state by its name
int findStateIndex(DFA *dfa, const char *stateName) {
    for (int i = 0; i < dfa->numStates; i++) {
        if (strcmp(dfa->stateNames[i], stateName) == 0) {
            return i;
        }
    }
    return -1; // State name not found
}

// Function to find the index of a symbol by its name
int findSymbolIndex(DFA *dfa, const char *symbolName) {
    for (int i = 0; i < dfa->numSymbols; i++) {
        if (strcmp(dfa->symbols[i], symbolName) == 0) {
            return i;
        }
    }
    return -1; // Symbol name not found
}

// Function to create DFA based on user input
void createDFA(DFA *dfa) {
    printf("Enter the number of states: ");
    scanf("%d", &(dfa->numStates));

    printf("Enter the names of the states:\n");
    for (int i = 0; i < dfa->numStates; i++) {
        printf("State %d name: ", i + 1);
        scanf("%s", dfa->stateNames[i]);
    }

    printf("\nEnter the number of symbols: ");
    scanf("%d", &(dfa->numSymbols));

    printf("Enter the symbols:\n");
    for (int i = 0; i < dfa->numSymbols; i++) {
        printf("Symbol %d name: ", i + 1);
        scanf("%s", dfa->symbols[i]);
    }

    char startStateName[MAX_STATE_NAME_LENGTH];
    printf("\nEnter the start state name: ");
    scanf("%s", startStateName);
    dfa->startState = findStateIndex(dfa, startStateName);

    int numAcceptStates;
    printf("\nEnter the number of accept states: ");
    scanf("%d", &numAcceptStates);

    printf("Enter the accept state names: ");
    for (int i = 0; i < numAcceptStates; i++) {
        char stateName[MAX_STATE_NAME_LENGTH];
        scanf("%s", stateName);
        int stateIndex = findStateIndex(dfa, stateName);
        if (stateIndex != -1) {
            dfa->acceptStates[stateIndex] = 1; // Mark state as accepting
        }
    }

    printf("\n");
    for (int i = 0; i < dfa->numStates; i++) {
        for (int j = 0; j < dfa->numSymbols; j++) {
            char nextStateName[MAX_STATE_NAME_LENGTH];
            printf("D['%s', '%s'] : ", dfa->stateNames[i], dfa->symbols[j]);
            scanf("%s", nextStateName);

            int nextState = findStateIndex(dfa, nextStateName);
            if (nextState != -1) {
                dfa->transition[i][j] = nextState;
            }
        }
    }
}

// Function to display the transition table
void displayTransitionTable(DFA *dfa) {
    printf("\nTransition Table:\n");
    printf("State\\Symbol");
    for (int i = 0; i < dfa->numSymbols; i++) {
        printf("\t%s", dfa->symbols[i]);
    }
    printf("\n");

    for (int i = 0; i < dfa->numStates; i++) {
        printf("%s", dfa->stateNames[i]);
        for (int j = 0; j < dfa->numSymbols; j++) {
            int nextState = dfa->transition[i][j];
            if (nextState != -1) {
                printf("\t%s", dfa->stateNames[nextState]);
            } else {
                printf("\t-");
            }
        }
        printf("\n");
    }
}

// Function to check if a string is accepted by the DFA and print transitions
int isAccepted(DFA *dfa, const char *input) {
    int currentState = dfa->startState;

    printf("Transition path: %s", dfa->stateNames[currentState]);

    for (int i = 0; i < strlen(input); i++) {
        char symbolName[MAX_SYMBOL_NAME_LENGTH];
        strncpy(symbolName, &input[i], 1);
        symbolName[1] = '\0';

        int symbolIndex = findSymbolIndex(dfa, symbolName);
        if (symbolIndex == -1) {
            printf("\nInvalid symbol '%s'.\n", symbolName);
            return 0; // Invalid symbol, string is rejected
        }

        int nextState = dfa->transition[currentState][symbolIndex];
        if (nextState == -1) {
            printf("\nInvalid transition on symbol '%s'.\n", symbolName);
            return 0; // Transition not defined, string is rejected
        }

        currentState = nextState;
        printf(" -> '%s' -> %s", symbolName, dfa->stateNames[currentState]);
    }

    printf("\n");
    return dfa->acceptStates[currentState];
}

int main() {
    DFA dfa;
    initializeDFA(&dfa);
    createDFA(&dfa);

    // Display the transition table
    displayTransitionTable(&dfa);

    char input[100];
    printf("Enter a string to check: ");
    scanf("%s", input);

    if (isAccepted(&dfa, input)) {
        printf("The string is accepted by the DFA.\n");
    } else {
        printf("The string is rejected by the DFA.\n");
    }

    return 0;
}
