#include <stdio.h>
#include <string.h>

#define MAX 100

// Productions
char prod[10][10];
int n;

// Function to check for possible reductions
int reduce(char stack[], int *top) {
    int i;

    // Check each production rule
    for (i = 0; i < n; i++) {
        char lhs = prod[i][0];
        char *rhs = prod[i] + 2;  // skip "X="

        int len_rhs = strlen(rhs);
        if (*top + 1 >= len_rhs) {
            int start = *top - len_rhs + 1;
            if (strncmp(stack + start, rhs, len_rhs) == 0) {
                // Reduction
                *top = start;
                stack[*top] = lhs;
                stack[*top + 1] = '\0';
                printf("Reduce by %c=%s, stack: %s\n", lhs, rhs, stack);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char input[MAX], stack[MAX];
    int top = -1, ip = 0;

    printf("Enter no. of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (no spaces, use X=rhs):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("Enter the input string: ");
    scanf("%s", input);

    int len = strlen(input);
    input[len] = '$';  // End of input marker
    input[len + 1] = '\0';

    stack[++top] = '$';  // Stack starts with end marker
    stack[top + 1] = '\0';

    printf("\nStack\tInput\tAction\n");
    while (1) {
        printf("%s\t%s\t", stack, input + ip);

        // Accept condition
        if (stack[top] == 'S' && stack[top - 1] == '$' && input[ip] == '$') {
            printf("ACCEPT\n");
            break;
        }

        // Try reduction
        if (reduce(stack, &top)) {
            continue;
        }

        // Else shift
        if (input[ip] != '\0') {
            stack[++top] = input[ip++];
            stack[top + 1] = '\0';
            printf("Shift\n");
        } else {
            printf("REJECT\n");
            break;
        }
    }

    return 0;
}
