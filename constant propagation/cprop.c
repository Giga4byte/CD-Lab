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


/*
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 26  // for variables a-z

char values[MAX][100];  // values of variables
int isConst[MAX];       // is the variable a constant?

int varIndex(char var) {
    return var - 'a';
}

void propagate(char *expr, char *out) {
    int i = 0, k = 0;
    while (expr[i]) {
        if (isalpha(expr[i])) {
            int idx = varIndex(expr[i]);
            if (isConst[idx]) {
                strcpy(&out[k], values[idx]);
                k += strlen(values[idx]);
            } else {
                out[k++] = expr[i];
            }
        } else {
            out[k++] = expr[i];
        }
        i++;
    }
    out[k] = '\0';
}

int main() {
    int n;
    char stmt[100], lhs, rhs[100], newRhs[100];

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (e.g., a=5, b=a):\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", stmt);
        lhs = stmt[0];
        strcpy(rhs, stmt + 2);  // skip 'a='

        propagate(rhs, newRhs);
        printf("%c = %s\n", lhs, newRhs);

        int idx = varIndex(lhs);
        strcpy(values[idx], newRhs);

        // Mark as constant if it's purely a number
        int isNum = 1;
        for (int j = 0; newRhs[j]; j++) {
            if (!isdigit(newRhs[j])) {
                isNum = 0;
                break;
            }
        }
        isConst[idx] = isNum;
    }

    return 0;
}
*/
