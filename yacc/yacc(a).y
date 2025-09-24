%{ 
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
int flag = 0; 
void yyerror(const char *); 
int yylex(void); 
%} 
 
%token NUM ID 
%left '+' '-' 
%left '*' '/' 
 
%% 
input: 
    expr '\n'    { } 
    | '\n'       { }       // allow empty line 
    ; 
 
expr: 
      expr '+' expr 
    | expr '-' expr 
    | expr '*' expr 
    | expr '/' expr 
    | '(' expr ')' 
    | NUM 
    | ID 
    ; 
%% 
 
/* Simple lexer implemented in the same file */ 
int yylex(void) { 
    int c; 
    // skip whitespace except newline 
    while ((c = getchar()) == ' ' || c == '\t') 
        ; 
    if (c == EOF) 
        return 0; 
 
    // Map newline so parser can use it 
    if (c == '\n') 
        return c; 
 
    // Number token 
    if (isdigit(c)) { 
        ungetc(c, stdin); 
        int val; 
        scanf("%d", &val); 
        return NUM; 
    } 
    // Identifier token 
    if (isalpha(c)) { 
        while (isalnum(c = getchar())) ; // Read rest 
of word 
        ungetc(c, stdin); 
        return ID; 
    } 
    // Single char tokens (operators, parenthesis) 
    return c; 
} 
 
void yyerror(const char *s) { 
    flag = 1; 
} 
 
int main(void) { 
    printf("Enter the expression: "); 
    if (yyparse() == 0 && flag == 0) 
        printf("The expression is VALID...\n"); 
    else 
        printf("The expression is INVALID...\n"); 
    return 0; 
}
