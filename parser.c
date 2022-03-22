#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"

char nextChar;
int isfileEmpty(FILE * ptr, char* c)
{
        if(ptr != NULL)
        {
                fseek(ptr, 0, SEEK_END);//set the pointer to the end of the file
                int test = ftell(ptr);

                if(test == 0)
                {
                        fprintf(stderr, "ERROR: %s: Input is empty\n", c);
                        return 1;
                }


        }
        else
        {
                fprintf(stderr, "ERROR: %s: Cannot open file\n", c);
                return 1;
        }

        fseek(ptr, 0, SEEK_SET); //reset the pointer back to the beginning of the file

        return 0;
}
int parser(char* fileName)
{
	struct token * tok;
	FILE * ptr = fopen(fileName, "r");
	if(isfileEmpty(ptr,"parser") == 1)
		return 0;
	nextChar = fgetc(ptr);

	//Start here
	
	fclose(ptr);
	return 1;
}
