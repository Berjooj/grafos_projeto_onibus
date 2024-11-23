#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

// Busca em profundidade
void buscaProfundidade(int origem, int destino, int* caminho, int* indiceCaminho, bool* encontrouCaminho) {
	int* pilha = (int*)malloc(grafo->numVertices * sizeof(int));
	int topo = -1;

	pilha[++topo] = origem;

	while (topo >= 0) {
		int atual = pilha[topo--];

		if (!grafo->lista[atual]->visitado) {
			grafo->lista[atual]->visitado = true;
			caminho[*indiceCaminho] = atual;
			(*indiceCaminho)++;

			if (atual == destino) {
				*encontrouCaminho = true;
				break;
			}

			Vertice* verticeAtual = grafo->lista[atual]->head;
			while (verticeAtual) {
				if (!grafo->lista[verticeAtual->vertex]->visitado)
					pilha[++topo] = verticeAtual->vertex;

				verticeAtual = verticeAtual->prox;
			}
		}
	}

	if (!(*encontrouCaminho)) {
		(*indiceCaminho) = 0;
	}

	free(pilha);
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