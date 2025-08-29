#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];   // input string
int i = 0;         // current input pointer
int error = 0;

// Function prototypes
void E();
void Eprime();
void T();
void Tprime();
void F();

void match(char expected) {
    if (input[i] == expected)
        i++;
    else {
        error = 1;
    }
}

// Grammar implementation
void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
    // else epsilon → do nothing
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(input[i])) {
        match(input[i]);
    } else {
        error = 1;
        i++;
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    E();

    if (!error && input[i] == '\0')
        printf("Parsing successful: string is valid\n");
    else
        printf("Parsing failed: string is invalid\n");

    return 0;
}
