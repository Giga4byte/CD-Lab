#include <stdio.h>
#include <string.h>

#define MAX 100

// set of productions
char prod[10][10];
int n;

// check for possible reductions
int reduce(char stack[], int *top) {
    int i;

    // check each production rule
    for (i = 0; i < n; i++) {
        char lhs = prod[i][0];
        char *rhs = prod[i] + 2;
        int len_rhs = strlen(rhs);
        
        if (*top + 1 >= len_rhs) {
            int start = *top - len_rhs + 1;
            if (strncmp(stack + start, rhs, len_rhs) == 0) {
                // reduction
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
    input[len] = '$';  // end of input
    input[len + 1] = '\0';

    stack[++top] = '$';  // since stack always starts with $
    stack[top + 1] = '\0';

    printf("\nStack\tInput\tAction\n");
    while (1) {
        printf("%s\t%s\t", stack, input + ip);

        // accept it
        if (stack[top] == 'S' && stack[top - 1] == '$' && input[ip] == '$') {
            printf("ACCEPT\n");
            break;
        }

        // reduce it
        if (reduce(stack, &top)) {
            continue;
        }

        // or shift
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
