#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct Aresta {
    int destino;
    int distancia;
    struct Aresta *proxima;
} Aresta;

typedef struct Vertice {
    char endereco[150];
    Aresta *lista_adj;
} Vertice;

typedef struct Grafo {
    Vertice *vertices;
    int quant_vertices;
    int capacidade;
} Grafo;

int adicionar_vertice(Grafo *grafo, const char *endereco);
void adicionar_aresta(Grafo *grafo, const char *origem, const char *destino, int distancia);
int encontrar_indice_vertice(Grafo *grafo, const char *endereco);
void liberar_grafo(Grafo *grafo);
Grafo* criar_grafo(int capacidade);

#endif