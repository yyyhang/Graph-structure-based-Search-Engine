#ifndef LLIST_H
#define LLIST_H

typedef struct Node *LList;

typedef struct Node{
    char content[60];			// how can I change to char *  ???
    LList next;
} LNode;

LList makeNode(char *);
LList insertSorted(LList, LList);
LList insert(LList, LList);
void freeLL(LList);
void showElement(LList);
int findIndex(LList, char *);
int valid(LList, char *);
int length(LList);
char *names(int,LList);

#endif