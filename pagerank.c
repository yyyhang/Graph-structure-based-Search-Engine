#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "collection.h"
#include "graph.h"
#include "LList.h"

typedef struct rank{
    char name[10];
    int index;
    int out;
    double value;
}rank;

double calInVer(Graph g, int k, double *PR,rank *);
void order(rank *pageR, int len);

int main(int argc, char *argv[]){
    FILE *f;        //file pointer
    char *word;
    int mark = 0;   // count the index of a letter in a word
    int i;

    // open collection.txt, and make a linked list for all links
    LList clt = getLinks();     // store all links from collection
    int len = length(clt);
    Graph g = newGraph(len);
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
        // start of section-1 to read urls
        while (1) {
            word = collect(f);
            if (strcmp(word,"start")==0 && mark == 0) {
                word = collect(f);
                if (strcmp(word, "section-1") == 0)
                    mark = 1;
            }
            else if (strcmp(word,"end")==0 && mark == 1) {
                word = collect(f);
                if (strcmp(word,"section-1")==0){
                    mark = 0;
                    break;
                }
            }
            else if (mark == 1)
                insertEdge(g,makeEdge(clt,tmp,word));       // connect the vertex
        }
        fclose(f);      // next file
        p = p->next;
    }

    p = clt;
    rank *pageR = malloc((g->nV)* sizeof(rank));
    for (i=0;i<g->nV;i++){
        strcpy(pageR[i].name,p->content);
        pageR[i].index = i;
        pageR[i].out = outDegree(g,i);
        p = p->next;
    }
    freeLL(clt);
    clt = NULL;

    if (argc != 4) {
        printf("Error!\n");
        return 1;
    }
    double d = strtod(argv[1],NULL);
    double diffPR = strtod(argv[2],NULL);
    int maxIteration = strtod(argv[3],NULL);

    double *PR = malloc((g->nV)* sizeof(double));
    double *prePR = malloc((g->nV)* sizeof(double));

    for (i=0; i<g->nV;i++)
        PR[i] = 1 / (double) g->nV;
    int iter = 0;
    double diff = diffPR;
    double factor = (double)(1-d)/g->nV;
    double sum;

    while (iter < maxIteration && diff >= diffPR){
        iter++;

        for (i=0; i<g->nV;i++)
            prePR[i] = PR[i];

        for (i=0; i<g->nV; i++){
            sum = calInVer(g, i, prePR, pageR);
            PR[i] = factor + d * sum;
            diff += fabs(PR[i] - prePR[i]);
        }
    }

    for (i=0;i<g->nV;i++)
        pageR[i].value = PR[i];
    free(PR);
    free(prePR);
    PR = NULL;
    prePR = NULL;
    order(pageR,len);

    //output
    f = fopen("pagerankList.txt", "w");
    for (i=0; i<g->nV;i++)
        fprintf(f,"%s, %d, %.7f\n",pageR[i].name,pageR[i].out,pageR[i].value);
    fclose(f);

    free(title);
    title = NULL;
    freeGraph(g);
    g=NULL;
    return 0;
}

double calInVer(Graph g, int k, double *PR, rank *pageR){
    int i;
    double sum = 0;
    for (i=0; i<g->nV; i++){
        if (g->edges[i][k] && i!=k){
            sum += (double) PR[i]/pageR[i].out;
        }
    }
    return sum;
}

void order(rank *pageR, int len) {
    int i, j;
    rank tmp;
    for (i = 1; i < len; i++) {
        if (pageR[i].value > pageR[i-1].value) {
            tmp = pageR[i];
            for (j = i - 1; j >= 0 && pageR[j].value < tmp.value; j--) {
                pageR[j + 1] = pageR[j];
            }
            pageR[j + 1] = tmp;
        }
    }
}