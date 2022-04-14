#ifndef TREE_H
#define TREE_H
#include "node.h"

struct node *createNode();
void preorder(struct node* ptr, int level);

#endif
