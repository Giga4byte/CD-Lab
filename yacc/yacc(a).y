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
    while ((c = getchar()) == ' ' || c == '\t'); 
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
        while (isalnum(c = getchar())) ; // Read rest of word 
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



/*

vae.l ------------------------------------------------
%{
 #include "y.tab.h"
 #include <math.h>
%}

%%
[0-9]+ {yylval = atoi(yytext); return NUM;}
[+] {return '+';}
[-] {return '-';}
[*] {return '*';}
[/] {return '/';}
[\t]+;
[\n] {return 0;}
%%

vae.y ------------------------------------------------
%{
 #include <stdio.h>
 #include <math.h>
%}

%token NUM
%left '-' '+' 
%left '*' '/'

%%
start: exp {printf ("%d\n", $$);}
exp:   exp '+' exp {$$=$1+$3;}
     | exp '-' exp {$$=$1-$3;}
     | exp '*' exp {$$=$1*$3;}
     | exp '/' exp {$$=$1/$3;}
     | '('exp')' {$$=$2;}
     | NUM {$$=$1;}
     ;
%%

main() {
 printf("Enter the expression:\n");
 if(yyparse() == 0) 
  { printf("SUCCESS\n"); } 
}
yywrap() {}
yyerror() { 
  printf("ERROR\n"); 
}

*/
