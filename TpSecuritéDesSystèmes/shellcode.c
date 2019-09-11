#include <stdio.h>

extern void code_start();
extern void code_end();

int main(void) {
        printf("Shellcode size = %d oct\n", code_end - code_start);

	char * i = (char *) code_start;

        printf("char * shellcode = { %#hhx ", *i);
        i++;

        while (i < (char *) code_end) {
          printf(", %#hhx", *i);
          i++;
        }

        printf("}\n");
        
        code_start(); 

        return 0;
}

