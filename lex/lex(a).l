%{ 
#include <stdio.h> 
int lines = 0, words = 0, chars = 0; 
%} 
 
%% 
 
\n        { lines++; } 
[ \t\n]+  { /* Ignore */ } 
[a-zA-Z0-9]+   { words++; } 
.         { chars++; } 
 
%% 
 
int main() { 
    yylex(); 
    printf("Lines: %d\n", lines); 
    printf("Words: %d\n", words); 
    printf("Characters: %d\n", chars); 
    return 0; 
} 
 
int yywrap() { 
    return 1;  
}
