%{
#include <stdio.h>

// State definitions
typedef enum { q0, q1, q2 } state_t;
state_t current_state = q0;

%}

%%

0 {
    switch(current_state) {
        case q0: current_state = q0; break;
        case q1: current_state = q0; break;
        case q2: current_state = q0; break;
    }
}

1 {
    switch(current_state) {
        case q0: current_state = q1; break;
        case q1: current_state = q2; break;
        case q2: current_state = q2; break;
    }
}

\n {
    if (current_state == q2) {
        printf("ACCEPT\n");
    } else {
        printf("REJECT\n");
    }
    current_state = q0; // Reset for the next input string
}

. {
    printf("Invalid character: %s\n", yytext);
    current_state = q0; // Reset on invalid input
}

%%

int main() {
    yylex();
    return 0;
}
