#include "tree.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct node * createNode(char * nodeN) {
	struct node * temp = (struct node *)malloc(sizeof(struct node));
	temp->firstN = temp->secondN = temp->thirdN = temp->fourthN = NULL;
	temp->fName = (char *)malloc(sizeof(nodeN) + 1);
	strcpy(temp->fName,nodeN);
	
	temp->arrToken = (struct token **) malloc(5*sizeof(struct token*));
	return temp;
}
void preorder(struct node* ptr, int level){
	if(ptr!=NULL){
		int i;
		for(i = 0; i < level;i++){
			printf(" ");
		}
		printf("%s ",ptr->fName);
		i = 0;
		while(ptr->arrToken[i]!= NULL && i < 5){
			printf("'%s' ",ptr->arrToken[i]->tokenIns);
			i++;
		}
	printf("\n");
        preorder(ptr->firstN, level+1);
        preorder(ptr->secondN, level+1);
        preorder(ptr->thirdN, level+1);
        preorder(ptr->fourthN, level+1);
	}

}
