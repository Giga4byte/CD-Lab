%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
    | input line
;

line:
      '\n'
    | expr '\n'   { printf("= %d\n", $1); }
;

expr:
      NUMBER             { $$ = $1; }
    | expr '+' expr      { $$ = $1 + $3; }
    | expr '-' expr      { $$ = $1 - $3; }
    | expr '*' expr      { $$ = $1 * $3; }
    | expr '/' expr      {
                            if ($3 == 0)
                                yyerror("division by zero");
                            else
                                $$ = $1 / $3;
                         }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'       { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
