#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

// Busca em profundidade
void buscaProfundidade(int origem, int destino, int* caminho, int* indiceCaminho, bool* encontrouCaminho) {
	grafo->lista[origem]->visitado = true;
	caminho[*indiceCaminho] = origem;
	(*indiceCaminho)++;

	if (origem == destino) {
		(*encontrouCaminho) = true;
		return;
	}

	Vertice* verticeAtual = grafo->lista[origem]->head;
	while (verticeAtual) {
		if (!grafo->lista[verticeAtual->vertex]->visitado) {
			buscaProfundidade(verticeAtual->vertex, destino, caminho, indiceCaminho, encontrouCaminho);

			if (grafo->lista[destino]->visitado) {
				return;
			}
		}

		verticeAtual = verticeAtual->prox;
	}

	// Desfaz o caminho se não encontrar o destino
	(*indiceCaminho)--;
	grafo->lista[origem]->visitado = false;
}

void profundidade(int origem, int destino) {
	int* caminho = (int*)malloc(grafo->numVertices * sizeof(int));
	int indiceCaminho = 0;
	bool encontrouCaminho = false;

	buscaProfundidade(origem, destino, caminho, &indiceCaminho, &encontrouCaminho);

	if (!encontrouCaminho) {
		printf("Nao existe caminho entre %s e %s.\n", grafo->lista[origem]->head->endereco, grafo->lista[destino]->head->endereco);
		system("pause");
		return;
	}

	printf("Caminho encontrado entre %d e %d: ", origem, destino);
	for (int i = 0; i < indiceCaminho; i++) {
		printf("%d ", caminho[i]);
	}

	printf("\n");
	system("pause");
}