#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define MAXLEN 100

typedef struct {
    char var;
    char value[MAXLEN];  // store propagated value (as string)
    int isConst;         // 1 if known constant
} Symbol;

Symbol table[MAX];
int symCount = 0;

// lookup variable in table
int lookup(char var) {
    for (int i = 0; i < symCount; i++) {
        if (table[i].var == var)
            return i;
    }
    return -1;
}

// insert or update variable
void update(char var, char *value, int isConst) {
    int idx = lookup(var);
    if (idx == -1) {
        table[symCount].var = var;
        strcpy(table[symCount].value, value);
        table[symCount].isConst = isConst;
        symCount++;
    } else {
        strcpy(table[idx].value, value);
        table[idx].isConst = isConst;
    }
}

// propagate constants in an expression
void propagate(char *expr, char *out) {
    int k = 0;
    for (int i = 0; expr[i]; i++) {
        if (isalpha(expr[i])) {
            int idx = lookup(expr[i]);
            if (idx != -1 && table[idx].isConst) {
                // substitute constant value
                for (int j = 0; table[idx].value[j]; j++)
                    out[k++] = table[idx].value[j];
            } else {
                out[k++] = expr[i];
            }
        } else {
            out[k++] = expr[i];
        }
    }
    out[k] = '\0';
}

int main() {
    int n;
    char stmt[MAXLEN];
    char lhs, rhs[MAXLEN], newRhs[MAXLEN];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (e.g., a=5, b=a+3):\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", stmt);
        lhs = stmt[0];
        strcpy(rhs, stmt + 2);

        propagate(rhs, newRhs);     // propagate constants
        printf("%c = %s\n", lhs, newRhs);

        // update symbol table
        if (isdigit(newRhs[0]) && strspn(newRhs, "0123456789") == strlen(newRhs)) {
            update(lhs, newRhs, 1); // mark as constant
        } else {
            update(lhs, newRhs, 0); // not a pure constant
        }
    }

    return 0;
}

