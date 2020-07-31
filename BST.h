#ifndef BST_H
#define BST_H

#include "LList.h"

typedef struct TNode *Tree;

typedef struct TNode{
    char word[40];
    LList urlList;
    Tree left;
    Tree right;
}TNode;

Tree newTNode(char *, char *);
Tree TreeInsert(Tree, char *, char *);
void inOrderTraversal(Tree);
LList TreeSearch(Tree, char *);
void freeTree(Tree);

#endif