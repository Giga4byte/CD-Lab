#include <stdio.h>
#include <string.h>

char input[100];   // input string
int i = 0;         // current input position
int error = 0;

// Function prototypes
void S();
void A();
void Aprime();
void B();
void match(char expected);

// Match function
void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        printf("Error: expected '%c' at position %d, found '%c'\n",
               expected, i, input[i]);
        error = 1;
    }
}

// Grammar functions
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
    // A' -> b c A' | ε
    if (input[i] == 'b' && input[i+1] == 'c') {
        match('b');
        match('c');
        Aprime();
    }
    // else epsilon → do nothing
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
