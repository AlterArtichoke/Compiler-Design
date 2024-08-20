%{
#include <stdio.h>

// State definitions
typedef enum { q0, q1, q2, q3 } state_t;
state_t current_state = q0;

%}

%%

0 {
    switch(current_state) {
        case q0: current_state = q1; break;
        case q1: current_state = q0; break;
        case q2: current_state = q3; break;
        case q3: current_state = q2; break;
    }
}

1 {
    switch(current_state) {
        case q0: current_state = q2; break;
        case q1: current_state = q3; break;
        case q2: current_state = q0; break;
        case q3: current_state = q1; break;
    }
}

\n {
    if (current_state == q1) {
        printf("ACCEPT\n");
    } else {
        printf("REJECT\n");
    }
    current_state = q0; // Reset for the next input string
}


