#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"

void exibirLista(Grafo *grafo) {
	for (int i = 0; i < grafo->numVertices; i++) {
		printf("Vertice %d - %s): ", i, grafo->lista[i]->head->endereco);
		Vertice *atual = grafo->lista[i]->head;
		atual = atual->prox;
		while (atual != NULL) {
			printf("\n");
			printf("    -> %d - %s (Distancia: %d) ", atual->vertex, atual->endereco, atual->distancia);
			atual = atual->prox;
		}
		printf("\n\n");
	}
}