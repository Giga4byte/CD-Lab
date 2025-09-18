#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return -1;
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        }
        else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }

    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

// Generate Three Address Code (TAC)
void generateTAC(char postfix[]) {
    char tempStack[100][10];
    int stTop = -1;
    int tempCount = 1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            char str[2] = {c, '\0'};
            strcpy(tempStack[++stTop], str);
        } else { // operator
            char op2[10], op1[10], temp[10];
            strcpy(op2, tempStack[stTop--]);
            strcpy(op1, tempStack[stTop--]);
            sprintf(temp, "t%d", tempCount++);
            printf("%s = %s %c %s\n", temp, op1, c, op2);
            strcpy(tempStack[++stTop], temp);
        }
    }
}

int main() {
    char infix[100], postfix[100];

    printf("Enter an expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("\nPostfix: %s\n", postfix);

    printf("\nThree Address Code (TAC):\n");
    generateTAC(postfix);

    return 0;
}
