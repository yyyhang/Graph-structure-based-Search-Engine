#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"
#include "graph.h"
#include "LList.h"

void printElement(LList head,FILE *f){
    if (head == NULL)
        fprintf(f,"\n");
    else{
        fprintf(f,"%s ",head->content);
        printElement(head->next,f);
    }
}

void inOrderOutput(Tree T,FILE *f){
    if (T){
        inOrderOutput(T->left,f);
        fprintf(f,"%s ",T->word);
        printElement(T->urlList,f);
        inOrderOutput(T->right,f);
    }
}

int main(){
    FILE *f;        //file pointer
    char *word;
    int mark = 0;   // count the index of a letter in a word

    // open collection.txt, and make a linked list for all links
    LList clt = getLinks();
    Tree T = NULL;
    LList p = clt;
    char *title= malloc(50);
    char *tmp;

    // open all the links in collection.txt one by one
    while (p){
        tmp = p->content;
        strcpy(title, tmp);
        strcat(title,".txt");
        if ((f = fopen (title, "r")) == NULL) {
            printf("Error!\n");
            return 1;
        }

        // start of section-2 to read words and related urls
        while (1) {
            word = collect(f);
            if (strcmp(word,"start")==0 && mark == 0) {
                word = collect(f);
                if (strcmp(word, "section-2") == 0)
                    mark = 2;
            }
            else if (strcmp(word,"end")==0 && mark == 2) {
                word = collect(f);
                if (strcmp(word,"section-2")==0){
                    mark = 0;
                    break;
                }
            }
            else if (mark == 2)
                T = TreeInsert(T, word, tmp);   // make a word and related urls as a node of a tree
        }
        fclose(f);
        p = p->next;
    }

    f = fopen("invertedIndex.txt", "w");
    inOrderOutput(T,f);
    fclose(f);

    free(title);
    freeTree(T);
	freeLL(clt);
    clt = NULL;
	title = NULL;
	T = NULL;
    return 0;
}


