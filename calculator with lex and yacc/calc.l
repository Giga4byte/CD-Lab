%{ 
    #include "y.tab.h" 
%} 
 
%% 
[0-9]+             { yylval = atoi(yytext); return NUMBER; } 
[ \t]+             { /* Ignore whitespace */ } 
\n                 { return '\n'; } 
[-+*/()]           { return yytext[0]; } 
.                  { printf("Invalid character: %s\n", yytext); return 0; } 
%% 
 
int yywrap() { return 1; } 
