#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "collection.h"

Graph newGraph(int v){
    // no need to check number of vertex, as it come from other function rather than inputting.
    Graph g = malloc(sizeof(GraphM));
    assert(g != NULL);
    g->nV = v;
    g->nE = 0;
    //allocate memory space for an array.
    g->edges = malloc(sizeof(int*)*v);
    assert (g->edges != NULL);
    //allocate memory space for the array of array, and initialize with 0.
    for (int i=0; i<g->nV;i++){
        g->edges[i] = calloc(v,sizeof(int));
        assert (g->edges[i] != NULL);
    }
    return g;
}

Edge makeEdge(LList head, Vertex v,Vertex w){
    Edge e;
    e.v = findIndex(head,v);
    e.w = findIndex(head,w);				// function from linked list, return the index of the string
    return e;
}

void insertEdge(Graph g, Edge e){
    if (!g->edges[e.v][e.w]){
        g->edges[e.v][e.w] = 1;
        g->nE++;
    }
}

void showGraph(Graph g,LList head) {
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
        for (j = 0; j < g->nV; j++)
            if (g->edges[i][j]){
                //printf("Edge %d - %d\n", i, j);
                printf("Edge %s - %s\n", names(i,head), names(j,head));
            }
}

void freeGraph(Graph g) {
    assert(g != NULL);
    int i;
    for (i = 0; i < g->nV; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
}
// This function comes from lecture materials


int outDegree(Graph g, int k){
    int i;
    int out = 0;
    for (i=0; i<g->nV; i++){
        if (i!=k && g->edges[k][i] !=0){
            out++;
        }
    }
    return out;
}

