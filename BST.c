#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "BST.h"

Tree newTNode(char *name, char *url){
    Tree T = malloc(sizeof(TNode));
    assert(T != NULL);
    T->left = NULL;
    T->right = NULL;
    strcpy(T->word, name);
    // T->urlList = NULL;		// Do I need to malloc or not here?
    T->urlList = makeNode(url);
    return T;
}

Tree TreeInsert(Tree T, char *name, char *url) {		// NB: it's not a void func. it returns Tree
    if (T == NULL)
        T = newTNode(name,url);
    else if (strcmp(name,T->word)<0)
        T->left = TreeInsert(T->left,name,url);
    else if (strcmp(name,T->word)>0)
        T->right = TreeInsert(T->right,name,url);
    else if (strcmp(name,T->word)==0){
        T->urlList = insertSorted(T->urlList, makeNode(url));
    }
    return T;
}

void inOrderTraversal(Tree T){
    if (T){
        inOrderTraversal(T->left);
        printf("%s ",T->word);
        showElement(T->urlList);
        inOrderTraversal(T->right);
    }
}

LList TreeSearch(Tree T, char *name) {
    LList C;
    if (T == NULL)
        C = NULL;
    else if (strcmp(name,T->word)<0)
        C = TreeSearch(T->left,name);
    else if (strcmp(name,T->word)>0)
        C = TreeSearch(T->right,name);
    else if (strcmp(name,T->word)==0){
        C = T->urlList;
    }
    return C;
}
// This function modified from lecture materials

void freeTree(Tree t) {
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
}
// This function comes from lecture materials