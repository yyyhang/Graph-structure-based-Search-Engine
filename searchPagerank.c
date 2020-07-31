#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "LList.h"
#include "BST.h"

#define MAXSTRING 1000

typedef struct Sear{
    char name[10];
    float value;
    int times;
}Sear;

void order(Sear *SPR, int len);

int main (int argc, char *argv[]) {
    char prl[3] = ", ";     //to split file pagerankList.txt
    char delim[2] = " ";    // to split words in invertedIndex.txt
    char *token;            // to hold words
    char word[30];
    char line[MAXSTRING] ;  // to hold each line
    FILE *f;
    Tree T = NULL;
    Sear *SPR = NULL;       // store links and related value
    int i;
    int leng;

    // open file pagerankList.txt and make a linked list for urls and pagerank value
    if ((f = fopen ("pagerankList.txt", "r")) == NULL) {
        printf("Error!\n");
        return (1);
    }
    leng=0;
    while(fgets(line, MAXSTRING, f) != NULL) {
        leng++;
    }
    SPR = malloc(leng * sizeof(Sear));
    assert(SPR!=NULL);
    rewind(f);
    i=0;
    // get url and related pagerank value
    while(fgets(line, MAXSTRING, f) != NULL) {
        strtok(line, "\n");
        /* first token */
        token = strtok(line, prl);
        strcpy(SPR[i].name , token);
        token = strtok(NULL, prl);
        token = strtok(NULL, prl);
        SPR[i].value = atof(token);
        SPR[i].times = 0;
        i++;
    }
    //Reference: This part is modified by code exTkns.c in sample file

    // open file invertedIndex.txt and make a tree to store words and associated links
    if ((f = fopen ("invertedIndex.txt", "r")) == NULL) {
        printf("Error!\n");
        return (1);
    }
    // get key words and related links
    while(fgets(line, MAXSTRING, f) != NULL)  {
        strtok(line, "\n");
        /* first token */
        token = strtok(line, delim);

        int count = 0;
        /* iterate over the rest of the tokens */
        while( token != NULL ) {
            if (count == 0) {
                strcpy(word,token);
                count++;
            }
            token = strtok(NULL, delim);
            if (count != 0 && token != NULL)
                T = TreeInsert(T, word, token);
        }
    }
    //Reference: This part is modified by code exTkns.c in sample file

    // search the key words
    LList other = NULL;
    int j;

    for (i = 1; i < argc; i++) {
        other = TreeSearch(T, argv[i]);
        while (other != NULL){
            for (j=0; j < leng; j++){
                if (strcmp(other->content,SPR[j].name)==0){
                    SPR[j].times++;
                    break;
                }
            }
            other = other->next;
        }
    }
    order(SPR, leng);

    // show results
    int cnt =0;
    i= 0;
    while (SPR[i].times>0 && cnt< 30){
        printf("%s \n", SPR[i].name);
        i++;
        cnt++;
    }

    // free memory space
    freeTree(T);
    free(SPR);
    SPR = NULL;
    T =NULL;
    return (0);
}

void order(Sear *SPR, int len) {
    int i, j;
    Sear tmp;
    for (i = 1; i < len; i++) {
        if (SPR[i].times > SPR[i-1].times) {
            tmp = SPR[i];
            for (j = i - 1; j >= 0 && SPR[j].times < tmp.times; j--) {
                SPR[j + 1] = SPR[j];
            }
            SPR[j + 1] = tmp;
        }
        // if have same words related, then order in pagerank value
        else if (SPR[i].times == SPR[i-1].times) {
            if (SPR[i].value > SPR[i-1].value) {
                tmp = SPR[i];
                for (j = i - 1; j >= 0 && SPR[j].value < tmp.value && SPR[i].times == SPR[i-1].times; j--) {
                    SPR[j + 1] = SPR[j];
                }
                SPR[j + 1] = tmp;
            }
        }
    }
}