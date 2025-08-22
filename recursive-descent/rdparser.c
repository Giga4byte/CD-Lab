#include <stdio.h>
#include <string.h>

char input[100];
int i = 0, error = 0;

void S();
void A();
void Aprime();
void B();

void match(char c) {
    if (input[i] == c) {
        i++;
    } else {
        printf("Error: expected '%c' at position %d, found '%c'\n", c, i, input[i]);
        error = 1;
    }
}

// S → a A B e
void S() {
    match('a');
    A();
    B();
    match('e');
}

// A → b A'
void A() {
    match('b');
    Aprime();
}

// A' → b c A' | ε
void Aprime() {
    if (input[i] == 'b' && input[i+1] == 'c') {
        match('b');
        match('c');
        Aprime();
    }
    // else epsilon → do nothing
}

// B → d
void B() {
    match('d');
}

int main() {
    printf("Enter the input string: ");
    scanf("%s", input);

    S();

    if (!error && input[i] == '\0')
        printf("Parsing successful: accepted ✅\n");
    else
        printf("Parsing failed: rejected ❌\n");

    return 0;
}
