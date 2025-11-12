#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NFA_STATES 8
#define MAX_INPUTS 8
#define MAX_DFA_STATES (1<<MAX_NFA_STATES)

int nfa[MAX_INPUTS][MAX_NFA_STATES][MAX_NFA_STATES];
int states, inputs, instate;
int dfa_states[MAX_DFA_STATES]; 
int dfa_tran[MAX_DFA_STATES][MAX_INPUTS];
int num_dfa_states = 0;

int get_dfa_state_index(int subset) {
    for (int i = 0; i < num_dfa_states; i++)
        if (dfa_states[i] == subset) return i;
    dfa_states[num_dfa_states++] = subset;
    return num_dfa_states - 1;
}

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

    for(int i = 0; i < inputs; i++) {
        printf("Enter matrix for variable %d:\n", input);
        for(int j = 0; j < states; j++)
            for(int k = 0; k < states; k++)
                scanf("%d", &nfa[i][j][k]);
    }

    num_dfa_states = 0;
    int queue[MAX_DFA_STATES], qfront=0, qrear=0;
    int initial = (1<<instate); 
    int initial_index = get_dfa_state_index(initial);
    queue[qrear++] = initial_index;

    memset(dfa_tran, -1, sizeof(dfa_tran));

    while(qfront < qrear) {
        int dfa_idx = queue[qfront++];
        int subset = dfa_states[dfa_idx];
        for (int i = 0; i < inputs; i++) {
            int next_subset = 0;
            for (int j = 0; j < states; j++) {
                if (subset & (1<<j)) {
                    for (int k = 0; k < states; k++)
                        if (nfa[i][j][k])
                            next_subset |= (1<<k);
                }
            }
            if (next_subset == 0) continue;
            int next_idx = get_dfa_state_index(next_subset);
            dfa_tran[dfa_idx][i] = next_idx;
            if (next_idx >= qrear) queue[qrear++] = next_idx;
        }
    }

    printf("\nDFA Transition Table:\n");
    printf("State\t\t\t");
    for (int i = 0; i < inputs; i++)
        printf("Input%d\t\t\t", i);
    printf("\n");

    for (int i = 0; i < num_dfa_states; i++) {
        print_subset(dfa_states[i]);
        printf("\t\t\t");
        for (int j = 0; j < inputs; j++) {
            if (dfa_tran[i][j] != -1)
                print_subset(dfa_states[dfa_tran[i][j]]);
            else
                printf("{}");
            printf("\t\t\t");
        }
        printf("\n");
    }

    return 0;
}
