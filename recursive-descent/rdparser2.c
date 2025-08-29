#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;
int error = 0;

void S();
void A();
void Aprime();
void B();
void match(char expected);

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error = 1;
    }
}

void S() {
    // S -> a A B e
    match('a');
    A();
    B();
    match('e');
}

void A() {
    // A -> b A'
    match('b');
    Aprime();
}

void Aprime() {
    // A' -> b c A' | #
    if (input[i] == 'b' && input[i+1] == 'c') {
        match('b');
        match('c');
        Aprime();
    }
}

void B() {
    // B -> d
    match('d');
}

int main() {
    printf("Enter a string to parse: ");
    scanf("%s", input);

    S();

    if (!error && input[i] == '\0')
        printf("Parsing successful: string is valid.\n");
    else {
        if (!error) // reached end with extra symbols
            printf("Error: extra symbols found at the end.\n");
        printf("Parsing failed: invalid string.\n");
    }

    return 0;
}
