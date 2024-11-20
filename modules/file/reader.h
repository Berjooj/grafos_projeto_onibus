#include <stdbool.h>
#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

#ifndef READER_H
#define READER_H

Grafo* criar_grafo(int numVertices);
void liberar_grafo(Grafo *grafo);
Vertice* adicionar_vertice(Grafo *grafo, const char *endereco, int vertex);
bool aresta_existe(Grafo *grafo, int origem, int destino);
void adicionar_aresta(Grafo *grafo, int origem, int destino, int distancia);
char* carregar_arquivo_json(const char *filename);
Grafo* parse_json_para_grafo(const char *json_string);

#endif
