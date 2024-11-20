#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct Vertice {
    int vertex;
    int distancia;
    char endereco[150];
    struct Vertice* prox;
} Vertice;

typedef struct ListaAdj {
    struct Vertice* head;
} ListaAdj;

typedef struct Grafo {
    int numVertices;
    struct ListaAdj ** lista;
} Grafo;

#endif