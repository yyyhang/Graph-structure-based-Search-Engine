#ifndef GRAPH_H
#define GRAPH_H

#include "BST.h"

typedef struct GraphM *Graph;

typedef char* Vertex;

typedef struct Edge {
    int v;
    int w;
} Edge;

typedef struct GraphM{
    int **edges;		//It finally points to integer.
    int nV;
    int nE;
}GraphM;

Graph newGraph(int);
Edge makeEdge(LList, Vertex,Vertex);
void insertEdge(Graph, Edge);
void showGraph(Graph,LList);
void freeGraph(Graph);
int outDegree(Graph, int);

#endif