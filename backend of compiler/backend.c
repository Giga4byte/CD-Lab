#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {
    char icode[10][30], str[20], opr[10];
    int i = 0;
    
    printf("Enter the set of 3AC (terminated by 'exit'):\n");

    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);
    
    printf("\nTARGET CODE GENERATION");
    
    i = 0;
    do {
        strcpy(str, icode[i]);
        switch (str[3]) {
            case '+':
                strcpy(opr, "ADD");
                break;
            case '-':
                strcpy(opr, "SUB");
                break;
            case '*':
                strcpy(opr, "MUL");
                break;
            case '/':
                strcpy(opr, "DIV");
                break;
            default:
                strcpy(opr, "UNKNOWN");
                break;
        }

        printf("MOV %c, R%d\n", str[2], i);
        printf("%s %c, R%d\n", opr, str[4], i);
        printf("MOV R%d, %c\n", i, str[0]); 
        
        i++; 
    } while (strcmp(icode[i], "exit") != 0); 
    
    getchar(); 
}
