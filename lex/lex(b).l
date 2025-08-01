%{ 
#include <stdio.h> 
%} 
 
%% 
 
[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+ {printf("Email 
Verified For: %s\n", yytext);} 
.  {/*ignore*/} 
\n  {/*ignore*/} 
 
%% 
 
int main() { 
    yylex(); 
    return 0; 
} 
 
int yywrap() { 
    return 1;  
} 
