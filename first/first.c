#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 10 // max = 10

char production[MAX][10];  // Store productions
char firstSet[10][10];     // Store FIRST sets
int n;                     // Number of productions

// Function prototypes
void findFirst(char *res, char c);
void addToResult(char *res, char val);

int main() {
    int i;
    char nonterminals[10], terminals[10];

    printf("Enter number of non-terminals: ");
    int n_nonterm; scanf("%d", &n_nonterm);

    printf("Enter non-terminals (single uppercase letters): ");
    for (i = 0; i < n_nonterm; i++)
        scanf(" %c", &nonterminals[i]);

    printf("Enter number of terminals: ");
    int n_term; scanf("%d", &n_term);

    printf("Enter terminals (single lowercase or symbols like ( ) + *): ");
    for (i = 0; i < n_term; i++)
        scanf(" %c", &terminals[i]);

    printf("Enter number of productions (MAX 10): ");
    scanf("%d", &n);

    printf("Enter productions in form A=bC (use 'e' for epsilon):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    // Compute FIRST sets
    for (i = 0; i < n; i++) {
        char lhs = production[i][0];
        char res[10] = "";
        findFirst(res, lhs);
        strcpy(firstSet[lhs - 'A'], res);
    }

    // Print FIRST sets
    printf("\n--- FIRST Sets ---\n");
    for (i = 0; i < n; i++) {
        char lhs = production[i][0];
        printf("FIRST(%c) = { %s }\n", lhs, firstSet[lhs - 'A']);
    }

    return 0;
}

// Recursive function to find FIRST of a symbol
void findFirst(char *res, char c) {
    int i;
    // If terminal, FIRST is the terminal itself
    if (!isupper(c)) {
        addToResult(res, c);
        return;
    }

    // If non-terminal → scan productions
    for (i = 0; i < n; i++) {
        if (production[i][0] == c) {
            // Look at RHS
            char rhs = production[i][2];

            if (rhs == 'e') {   // epsilon
                addToResult(res, 'e');
            }
            else if (!isupper(rhs)) {  // terminal
                addToResult(res, rhs);
            }
            else {  // non-terminal → recursive call
                findFirst(res, rhs);
            }
        }
    }
}

// Add a symbol to result (avoid duplicates)
void addToResult(char *res, char val) {
    int i;
    for (i = 0; res[i] != '\0'; i++) {
        if (res[i] == val) return; // already present
    }
    int len = strlen(res);
    res[len] = val;
    res[len + 1] = '\0';
}
