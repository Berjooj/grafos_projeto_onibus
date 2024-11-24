#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

// Busca em profundidade
void buscaProfundidade(int origem, int destino, int* percurso, int* indicePercurso, bool* encontrouPercurso) {
	int* pilha = (int*)malloc(grafo->numVertices * sizeof(int));
	int topo = -1;

	pilha[++topo] = origem;

	while (topo >= 0) {
		int atual = pilha[topo--];

		if (!grafo->lista[atual]->visitado) {
			grafo->lista[atual]->visitado = true;
			percurso[*indicePercurso] = atual;
			(*indicePercurso)++;

			if (atual == destino) {
				(*encontrouPercurso) = true;
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

	if (!(*encontrouPercurso)) {
		(*indicePercurso) = 0;
	}

	free(pilha);
}

void profundidade(int origem, int destino) {
	int* percurso = (int*)malloc(grafo->numVertices * sizeof(int));
	int indicePercurso = 0;
	bool encontrouPercurso = false;

	buscaProfundidade(origem, destino, percurso, &indicePercurso, &encontrouPercurso);

	if (!encontrouPercurso) {
		free(percurso);
		printf("Nao existe percurso entre %s e %s.\n", grafo->lista[origem]->head->endereco, grafo->lista[destino]->head->endereco);
		system("pause");
		return;
	}

	printf("Percurso encontrado entre %d e %d: ", origem, destino);
	for (int i = 0; i < indicePercurso; i++) {
		printf("%d ", percurso[i]);
	}

	free(percurso);
	printf("\n");
	system("pause");
}

void _profundidade(int origem, int destino) {
	int* percurso = (int*)malloc(grafo->numVertices * sizeof(int));
	int indicePercurso = 0;
	bool encontrouPercurso = false;

	buscaProfundidade(origem, destino, percurso, &indicePercurso, &encontrouPercurso);
	resetarVisita();
	free(percurso);
}