// lexical analysis - compiler design

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 	

#define MAX 100

char *words[] = {"if", "int", "return", "float", "FILE"};

int main () {
	FILE *fp = fopen ("input.txt", "r");
	char ch;
	
	if (fp == NULL) {
		printf("... Couldn't open file\n");
	} 
	
	while ((ch = getc(fp)) != EOF) {
	
		// Operator case
		if (ch == '=') {
			printf ("%c is an equal to operator\n", ch);
		} else if (ch == '+') {
			printf ("%c is an addition operator\n", ch);
		} else if (ch == '-') {
			printf ("%c is an subtraction operator\n", ch);
		} else if (ch == '*') {
			printf ("%c is an multiplication operator\n", ch);
		} else if (ch == '/') {
			printf ("%c is an division operator\n", ch);
		}
		
		// Space case
		if (ch == ' ' || ch == '	') {
			continue;
		}
		
		// Comment case
		if (ch == '/') {
            ch = getc(fp);
            if (ch == '/') {
                printf("// is a comment, so we will ignore that line\n");
                while ((ch = getc(fp)) != '\n' && ch != EOF);
            }
        }
        
        // Punctuation case
        if (ch == ',') {
        	printf("%c is a comma punctuation\n", ch);
        } else if (ch == ';') {
			printf ("%c is a semi-colon operator\n", ch);
		}
        
        // Digit case
        if (isdigit(ch)) {
        	char num[MAX];
            int num_index = 0;
            while (isdigit(ch) || ch == '.') {
                num[num_index++] = ch;
                ch = getc(fp);
            }
            
            num[num_index] = '\0';
            printf("%s is a number\n", num);
            
            if (ch != EOF) {
                ungetc(ch, fp);
            }
        }
        
        // Keyword case
        if (isalpha(ch)) {
        	char num[MAX];
            int num_index = 0;
            while (isalpha(ch)) {
                num[num_index++] = ch;
                ch = getc(fp);
            }
            
            num[num_index] = '\0';
            // compare with words[] 
            int flag = 0;
            for (int i=0; i<sizeof(words)/sizeof(words[0]); i++) {
				if (strcmp(num, words[i]) == 0) {
					printf("%s is a keyword\n", num);
					flag = 1;
					break;
				} 
			}
			
			if (!flag) {
				printf("%s is a identifier\n", num);
			}
			
            if (ch != EOF) {
                ungetc(ch, fp);
            }
        }
	}
	
	return 0;
}
