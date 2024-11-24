#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include "types.h"

Grafo *criar_grafo(int numVertices);
void liberar_grafo(Grafo *grafo);
int buscar_vertice_por_endereco(Grafo *grafo, const char *endereco);
Vertice *adicionar_vertice(Grafo *grafo, const char *endereco, int vertex);
bool aresta_existe(Grafo *grafo, int origem, int destino);
void adicionar_aresta(Grafo *grafo, int origem, int destino, int distancia);
void init(int lerArquivo, char *nome_arquivo);
void limparTela();
void resetarVisita();

#endif
