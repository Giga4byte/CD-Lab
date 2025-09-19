#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a TAC instruction
typedef struct {
    char result[10];  // Variable receiving the result
    char arg1[10];    // First operand
    char arg2[10];    // Second operand
    char op[3];       // Operator (e.g., +, -, *, /)
} TAC;

// Array to simulate the registers
char *registers[] = {"AX", "BX", "CX", "DX", "SI", "DI", "SP", "BP"};
int reg_index = 0; // To cycle through the registers

// Function to get a new register
char* get_register() {
    if (reg_index == 8) reg_index = 0; // Reset after using all registers
    return registers[reg_index++];
}

// Function to generate the 8086 assembly code from TAC
void generate_assembly(TAC *tac, int tac_size) {
    // Iterate through TAC instructions
    for (int i = 0; i < tac_size; i++) {
        printf("; %s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);

        if (strcmp(tac[i].op, "*") == 0) {
            // Multiply
            printf("MOV AX, %s\n", tac[i].arg1);  // Load first operand into AX
            printf("MUL %s\n", tac[i].arg2);      // Multiply AX with second operand
            printf("MOV %s, AX\n", tac[i].result); // Store the result in the result variable
        } else if (strcmp(tac[i].op, "+") == 0) {
            // Add
            char *reg = get_register();
            printf("MOV %s, %s\n", reg, tac[i].arg1);  // Load first operand into a register
            printf("ADD %s, %s\n", reg, tac[i].arg2);  // Add second operand to register
            printf("MOV %s, %s\n", tac[i].result, reg); // Store the result in the result variable
        } else if (strcmp(tac[i].op, "-") == 0) {
            // Subtract
            char *reg = get_register();
            printf("MOV %s, %s\n", reg, tac[i].arg1);  // Load first operand into a register
            printf("SUB %s, %s\n", reg, tac[i].arg2);  // Subtract second operand from register
            printf("MOV %s, %s\n", tac[i].result, reg); // Store the result in the result variable
        } else if (strcmp(tac[i].op, "=") == 0) {
            // Simple assignment (MOV)
            printf("MOV %s, %s\n", tac[i].result, tac[i].arg1); // Direct move
        }
        printf("\n");
    }
}

int main() {
    int tac_size = 5;
    TAC tac[5];

    // Sample input
    // a = a * b
    // c = f * h
    // g = a * h
    // f = Q + w
    // t = q + j

    // Fill the TAC array with user input
    strcpy(tac[0].result, "a");
    strcpy(tac[0].arg1, "a");
    strcpy(tac[0].op, "*");
    strcpy(tac[0].arg2, "b");

    strcpy(tac[1].result, "c");
    strcpy(tac[1].arg1, "f");
    strcpy(tac[1].op, "*");
    strcpy(tac[1].arg2, "h");

    strcpy(tac[2].result, "g");
    strcpy(tac[2].arg1, "a");
    strcpy(tac[2].op, "*");
    strcpy(tac[2].arg2, "h");

    strcpy(tac[3].result, "f");
    strcpy(tac[3].arg1, "Q");
    strcpy(tac[3].op, "+");
    strcpy(tac[3].arg2, "w");

    strcpy(tac[4].result, "t");
    strcpy(tac[4].arg1, "q");
    strcpy(tac[4].op, "+");
    strcpy(tac[4].arg2, "j");

    // Generate 8086 Assembly
    printf("Generated 8086 Assembly:\n");
    generate_assembly(tac, tac_size);

    return 0;
}
