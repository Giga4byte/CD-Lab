%{ 
#include <stdio.h> 
int vow = 0, cons = 0; 
%} 
 
%% 
[aAeEiIoOuU]                  { vow++; } 
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   { cons++; } 
.|\n                { /* Ignore other characters */ } 
%%

int main(int argc, char **argv) { 
  printf("Enter a string:\n"); 
  yylex(); 
  printf("Total vowels: %d\n", vowels); 
  printf("Total consonants: %d\n", consonants); 
  return 0;
}

int yywrap() { 
return 1; 
}
