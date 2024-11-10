#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"

void exibirLista(Grafo *grafo) {
    for (int i = 0; i < grafo->quant_vertices; i++) {
        printf("[%d] Vertice %s:" , i , grafo->vertices[i].endereco);
        Aresta *aresta = grafo->vertices[i].lista_adj;
        while (aresta) {
            printf(" -> [%d] %s (Distancia: %d)", aresta->destino, grafo->vertices[aresta->destino].endereco, aresta->distancia);
            aresta = aresta->proxima;
        }
        printf("\n");
    }
}