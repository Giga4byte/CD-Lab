%{ 
#include <stdio.h> 
#include <ctype.h> 
int yylex(void); 
void yyerror(const char *s) { printf("Invalid 
input!\n"); } 
%} 
 
%token ID NUM 
 
%% 
input: 
    /* Accepts zero or more IDs or NUMs */ 
    /* Keeps parsing until end of input */ 
    | input token 
    ; 
 
token: 
      ID  { printf("Valid identifier!\n"); } 
    | NUM { printf("Invalid identifier!\n"); } 
    ; 
%% 
 
int yylex(void) { 
    int c; 
 
    // Skip whitespace 
    while ((c = getchar()) == ' ' || c == '\t' || c == 
'\n') 
        ; 
 
    if (c == EOF) 
        return 0; 
 
    // Match number: [0-9]+ 
    if (isdigit(c)) { 
        while (isdigit(c = getchar())) ; 
        ungetc(c, stdin); 
        return NUM; 
    } 
 
    // Match identifier: [a-zA-Z_][a-zA-Z0-9_]* 
    if (isalpha(c) || c == '_') { 
        while (isalnum(c = getchar()) || c == '_') 
            ; 
        ungetc(c, stdin); 
        return ID; 
    } 
 
    // Anything else: not valid 
    return c; 
} 
 
int main(void) { 
    printf("Enter something:\n"); 
    yyparse(); 
    return 0; 
} 
