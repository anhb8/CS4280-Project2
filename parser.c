#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"

char nextChar;
struct token * tok;
FILE * ptr = NULL;
int isConsumed = 1;  
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
	ptr = fopen(fileName, "r");
	if(isfileEmpty(ptr,"parser") == 1)
		return 0;
	nextChar = fgetc(ptr);
	filter();

	program();
	//Start here
		
	fclose(ptr);
	return 1;
}

void printpError(int errorCode){
	switch(errorCode) {
	case 100:
		printf("Error: Expect 'main',but received %s (Line: %d, Character: %d)\n",
		tok->tokenIns,tok->line,tok->charN);
		break;
	case 101:
		printf("Error: The token is not 'Identifier',but received %s (Line: %d, Character: %d)\n",
                  tok->tokenIns,tok->line,tok->charN);
		break;
	case 102:
		printf("Error:The token is not ':=',but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
		break;
	case 103:
		printf("Error: The token is not 'whole',but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
		break;
	case 104:
		printf("Error:The token is not ';'but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
		break;
	case 105:   
                printf("Error:The token is not '{' but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
                break;
	case 106:   
                printf("Error:The token is not '}'but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
                break;
	case 107:   
                printf("Error:The token is not ';',but received %s (Line: %d, Character: %d)\n",
                tok->tokenIns,tok->line,tok->charN);
                break;
	case 108:   
                printf("Error:The token is not 'listen',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 110:
                printf("Error:The token is not 'yell',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 111:
                printf("Error:The token is not 'if',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 112:
                printf("Error:The token is not '[',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 113:
                printf("Error:The token is not ']',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 114:
                printf("Error:The token is not 'then',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 115:
                printf("Error:The token is not 'until',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 116:
                printf("Error:The token is not 'assign',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 118:
                printf("Error:The token is not '=',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 121:
                printf("Error:The token is not 'label',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
	case 122:
                printf("Error:The token is not 'portal',but received %s (Line: %d, Character: %d)\n",tok->tokenIns,tok->line,tok->charN);
                break;
        }  
	printf("Error code: %d\n",errorCode);
	exit(1);
}

void filter(){
	if(isConsumed == 1){
		tok = FSADriver(ptr);
		while(tok->tokenID == COMMENT)
			tok = FSADriver(ptr);
	}else{
		isConsumed = 1;
	}
}

void vars() {
	if (strcmp(tok->tokenIns,"declare")==0) {
		filter();
		if (tok->tokenID != IDENT) {
			printpError(101);	
		}
		filter();
		
		if(strcmp(tok->tokenIns,":=")!=0) {
			printpError(102);
		}
		filter();
		if (strcmp(tok->tokenIns,"whole")!=0) {
			printpError(103);
		}
		filter();
		if (strcmp(tok->tokenIns,";")!=0) {
                        printpError(104);
                }
		filter();
		vars();   	
	}else 
		isConsumed = 0;
}

void program() {
	vars();

	filter();
	if (strcmp(tok->tokenIns,"main")!=0) {
		printpError(100);
	}
	
	filter();
	block();
}

void block(){	
	if(strcmp(tok->tokenIns,"{")!=0) {
		printpError(105);
	}
	
	else {
		filter();
		vars();
		filter();
		stats();
		filter();
		if(strcmp(tok->tokenIns,"}")!=0) {
			printpError(106);
		}
	}
}

void stats(){
	stat();
	filter();
	mStat();
}

void  mStat(){
	if(tok->tokenID == KEYWORD || strcmp(tok->tokenIns, "{") == 0) {
		stat();
		filter();
		mStat();
	}

	else 
		isConsumed=0;
}


void stat(){
	int isBlock = 0;
	if(tok->tokenID == KEYWORD || strcmp(tok->tokenIns, "{") == 0){
		if(strcmp(tok->tokenIns,"listen")==0) {
			in();						
		}

		else if (strcmp(tok->tokenIns,"yell")==0) {
			out();
		}

		else if (strcmp(tok->tokenIns,"{")==0) {
			block();
			isBlock=1;
		}

		else if (strcmp(tok->tokenIns,"if")==0) {
                         if1();
                 }

		else if (strcmp(tok->tokenIns,"repeat")==0) {
                         loop();
                 }
		
		else if (strcmp(tok->tokenIns,"assign")==0) {
                         assign();
                 } 

		else if (strcmp(tok->tokenIns,"portal")==0) {
                         goto1();
                 } 

		else if (strcmp(tok->tokenIns,"label")==0) {
                         label();
                 } 
		 
	}else
		printpError(121);//expect a statement
	
	if(isBlock != 1){
		filter();
		//check ;
	}
		
}

void loop(){
	if (strcmp(tok->tokenIns,"repeat")!=0) {
		printpError(122);
	}
	
	else{
		filter();
		if (strcmp(tok->tokenIns,"[")==0) {
			loop1();
		}

		else 
			loop2();
	}
}
void in() {
	if(strcmp(tok->tokenIns,"listen")!=0) {
                printpError(108);
        } 
	filter();

	if (tok->tokenID != IDENT) {
             printpError(101);    
        }  
}

void out() {
	  if(strcmp(tok->tokenIns,"yell")!=0) {
                printpError(110);
        } 
	
	filter();
	expr();
}

void expr() {
	N();

	filter();
	if(strcmp(tok->tokenIns,"-")!=0) {
                isConsumed=0;
        }

	else {
		filter();
		expr();
	} 
}
void N(){
	A();
	filter();
	N1();
}

void N1() {
	if(strcmp(tok->tokenIns,"/")==0) {
		filter();
		A();
		filter();
		N1();	
	}

	else if(strcmp(tok->tokenIns,"+")==0) {
		filter();
		A();
		filter();
		N1();
	}

	else
		isConsumed=0;
		

}

void A() {
	M();
	filter();
	if(strcmp(tok->tokenIns,"*")!=0) {
		isConsumed=0;
	}

	else {
		filter();
		A();
	}
}

void M() {
	if(strcmp(tok->tokenIns,"%")==0) {
		filter();
		M();
	}

	else 
		R();
}

void R() {
	if(strcmp(tok->tokenIns,"(")==0) {
		filter();
		expr();
		filter();
		if(strcmp(tok->tokenIns,")")!=0)
			printpError(123);
	}
	
	else if (tok->tokenID == IDENT || tok->tokenID == NUMBER) {
		printf("Token %s consumed\n", tok->tokenIns);
	}

	else
		printpError(124); //expect identifier or number 
}
void if1() {
	if(strcmp(tok->tokenIns,"if")!=0) {
                printpError(111);
        } 
	
	else {
		filter();
		 if(strcmp(tok->tokenIns,"[")!=0) {
                	printpError(112);
       		 }

		else {
			filter();
			expr();
			filter();
			R0();
			filter();
			expr();
			filter();
			if(strcmp(tok->tokenIns,"]")!=0) {
                		printpError(113);
        		}	 
			
			else {
				filter();
				 if(strcmp(tok->tokenIns,"then")!=0) {
               				 printpError(114);
        			 }

				else {
					filter();
					stat();
				} 
			} 
	
		}	 		
	}
}

void loop1() {
	if(strcmp(tok->tokenIns,"[")!=0) {
                printpError(112);
        } 
		
	else {
			filter();
			expr();
			filter();
			R0();
			filter();
			expr();
			filter();
			if(strcmp(tok->tokenIns,"]")!=0) {
                		printpError(113);
        		}

			else {
				filter();
				stat();
			} 			
	}
}

void loop2() {
		stat();
		filter();
		if(strcmp(tok->tokenIns,"until")!=0) {
                	printpError(115);
        	}
		
		else {
			filter();
			if(strcmp(tok->tokenIns,"[")!=0) {
                		printpError(112);
        		} 
			
			else {
				filter();
				expr();
				filter();
				R0();
				filter();
				expr();
				filter();
				if(strcmp(tok->tokenIns,"]")!=0) {
                			printpError(113);
        			} 
			}
		} 
}

void assign() {
	if(strcmp(tok->tokenIns,"assign")!=0) {
                printpError(116);
        }

	else {
		filter();
		if (tok->tokenID != IDENT) {
                        printpError(101);    
                } 
		
		else {
			filter();
			if(strcmp(tok->tokenIns,"=")!=0) {
               			printpError(118);
        		}

			else {
				filter();
				expr();				
			} 			

		} 
	} 
}

void R0() {
	if(strcmp(tok->tokenIns,">=")==0 || strcmp(tok->tokenIns,"<=")==0 || 
		strcmp(tok->tokenIns,"==")==0 || strcmp(tok->tokenIns,"!=")==0 ) {
              //attach toekn to the node;
              printf("Consumed token %s\n",tok->tokenIns);
        }
	
	else if (strcmp(tok->tokenIns,".")==0 ) {
		filter();
		if(strcmp(tok->tokenIns,".")==0) {
			filter();
			if(strcmp(tok->tokenIns,".")==0) {
				//attach token to the node
			}
			
			else 
				printpError(119);
	
	
		}
		else
			printpError(119); 
	}

	else 
		printpError(120);


	  

}

void label(){
	if(strcmp(tok->tokenIns,"label")!=0) {
                printpError(121);
        }

	else {
		filter();
		if (tok->tokenID != IDENT) {
                        printpError(101);    
                }  
	} 
}

void goto1(){
	if(strcmp(tok->tokenIns,"portal")!=0) {
                printpError(122);
        } 

	else {
		filter();
		if (tok->tokenID != IDENT) {
                        printpError(101);    
                } 
	}
}

