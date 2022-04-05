#ifndef PARSER_H
#define PARSER_H

int isfileEmpty(FILE* ptr, char* c);
int parser(char* fileName);
void filter();
void program();
void vars();
void block();
void expr();
void N();
void N1();
void A();
void M();
void R();
void stats();
void mStat();
void stat();
void in();
void out();
void if1();
void loop1();
void loop2();
void loop();
void assign();
void R0();
void label();
void goto1();
#endif
