// most of the coed are modified from lecture materials

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "LList.h"

int length(LList head){
    LList p = head;
    int i = 0;
    while (p){
        p = p->next;
        i++;
    }
    return i;
}

void freeLL(LList L) {
    if (L != NULL) {
        freeLL(L->next);
        free(L);
    }
}

// Pack the new string as a node
LList makeNode(char *string){
    LList n = malloc(sizeof(LNode));
    assert(n != NULL);
    n->next = NULL;
    strcpy(n->content,string);
    return n;
}

// insert the new node into linked list with order
LList insertSorted(LList head, LList node){
    if (head == NULL || strcmp(node->content,head->content)<0){
        node->next = head;
        return node;
    }
    if (strcmp(node->content,head->content)==0)
        return head;

    head->next = insertSorted(head->next, node);
    return head;
}

LList insert(LList head, LList node){
    node->next = head;
    return node;
}

void showElement(LList head){
    if (head == NULL)
        putchar('\n');
    else{
        printf("%s ",head->content);
        showElement(head->next);
    }
}

//giving the name and return index
int findIndex(LList head, char *name){
    int i = 0;
    LList tmp = head;
    assert (tmp	!= NULL);
    while (tmp){
        if (strcmp(name,tmp->content)==0)
            return i;
        else{
            i++;
            tmp = tmp->next;
        }
    }
    return -1;
}

// Check if the content in the linked list
int valid(LList head, char *name){
    LList tmp = head;
    while (tmp){
        if (strcmp(name,tmp->content)==0)
            return 1;
        else{
            tmp = tmp->next;
        }
    }
    return 0;
}

//giving the index and return names
char *names(int K,LList head){
    LList p = head;
    for (int i = 0; i < K; i++)
        p = p->next;
    return p->content;
}