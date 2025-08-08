#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NFA_STATES 8
#define MAX_INPUTS 8
#define MAX_DFA_STATES (1<<MAX_NFA_STATES)    // Power set

// Each DFA state is represented as a bitmask: bit i set -> NFA state i present
int nfa[MAX_INPUTS][MAX_NFA_STATES][MAX_NFA_STATES]; // [input][from][to]
int states, inputs, instate;

// DFA structures
int dfa_states[MAX_DFA_STATES];      // bitmask representing each DFA state (subset of NFA states)
int dfa_tran[MAX_DFA_STATES][MAX_INPUTS]; // DFA transitions: [dfa_state_index][input] = index of next DFA state
int num_dfa_states = 0;

// Find index of subset in dfa_states, add it if not found.
// Returns (index of subset, 1 if newly added)
int get_dfa_state_index(int subset) {
    for (int i = 0; i < num_dfa_states; i++)
        if (dfa_states[i] == subset) return i;
    // New state!
    dfa_states[num_dfa_states++] = subset;
    return num_dfa_states - 1;
}

// Helper: Print a DFA state as {q0,q1}
void print_subset(int subset) {
    printf("{");
    int started = 0;
    for (int i = 0; i < states; i++) {
        if (subset & (1<<i)) {
            if (started) printf(",");
            printf("q%d", i);
            started = 1;
        }
    }
    printf("}");
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &states);
    printf("Enter number of inputs: ");
    scanf("%d", &inputs);
    printf("Enter initial state: ");
    scanf("%d", &instate);

    // Read NFA transition table
    for(int input = 0; input < inputs; input++) {
        printf("Enter NFA matrix for input %d as %d rows of %d numbers (0 or 1):\n", input, states, states);
        for(int from = 0; from < states; from++)
            for(int to = 0; to < states; to++)
                scanf("%d", &nfa[input][from][to]);
    }

    // DFA construction by subset method
    num_dfa_states = 0;
    int queue[MAX_DFA_STATES], qfront=0, qrear=0;

    int initial = (1<<instate);                       // Initial DFA state (bitmask)
    int initial_index = get_dfa_state_index(initial);
    queue[qrear++] = initial_index;                   // Start with initial state

    // Mark all dfa_tran as -1 initially
    memset(dfa_tran, -1, sizeof(dfa_tran));

    while(qfront < qrear) {
        int dfa_idx = queue[qfront++];
        int subset = dfa_states[dfa_idx];
        // For each input, compute target subset
        for (int inp = 0; inp < inputs; inp++) {
            int next_subset = 0;
            // For each NFA state in this subset
            for (int s = 0; s < states; s++) {
                if (subset & (1<<s)) {
                    // For each NFA target
                    for (int t = 0; t < states; t++)
                        if (nfa[inp][s][t])
                            next_subset |= (1<<t);
                }
            }
            if (next_subset == 0) continue; // Dead state; can omit or include if desired
            int next_idx = get_dfa_state_index(next_subset);
            dfa_tran[dfa_idx][inp] = next_idx;
            // If it's a new state, add to queue
            if (next_idx >= qrear) queue[qrear++] = next_idx;
        }
    }

    // Print DFA transition table
    printf("\nDFA Transition Table:\n");
    printf("%-15s", "States");
    for (int i = 0; i < inputs; i++)
        printf("Input %d        ", i);
    printf("\n");

    for (int i = 0; i < num_dfa_states; i++) {
        print_subset(dfa_states[i]);
        printf("%*s", 15 - 2*states, " ");    // Spacing
        
        for (int inp = 0; inp < inputs; inp++) {
            if (dfa_tran[i][inp] != -1)
                print_subset(dfa_states[dfa_tran[i][inp]]);
            else
                printf("{}");
            printf("%*s", 15 - 2*states, " ");
        }
        printf("\n");
    }

    return 0;
}
