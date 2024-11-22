#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

void floydWarshall(int **dist, int **next) {
	for (int k = 0; k < grafo->numVertices; k++) {
		for (int i = 0; i < grafo->numVertices; i++) {
			for (int j = 0; j < grafo->numVertices; j++) {
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
					dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

int *reconstruirCaminho(int origem, int destino, int **next, int *tamanhoCaminho) {
	if (next[origem][destino] == -1) {
		*tamanhoCaminho = 0;
		return NULL;
	}

	int *caminho = (int *)malloc(grafo->numVertices * sizeof(int));
	int indice = 0;
	int atual = origem;

	while (atual != destino) {
		caminho[indice++] = atual;
		atual = next[atual][destino];
	}
	caminho[indice++] = destino;

	*tamanhoCaminho = indice;
	return caminho;
}

void imprimirFloyd(int *caminho, int tamanhoCaminho, int origem, int destino) {
	if (caminho == NULL || tamanhoCaminho == 0) {
		printf("Nao existe caminho entre %d e %d.\n", grafo->lista[origem]->head->vertex, grafo->lista[destino]->head->vertex);
	} else {
		printf("Caminho encontrado entre %d e %d: ", grafo->lista[origem]->head->vertex, grafo->lista[destino]->head->vertex);

		int pesoTotal = 0;
		for (int i = 0; i < tamanhoCaminho - 1; i++) {
			int atual = caminho[i];
			int prox = caminho[i + 1];

			Vertice *adj = grafo->lista[atual]->head;
			while (adj != NULL && adj->vertex != prox) {
				adj = adj->prox;
			}
			if (adj != NULL) {
				pesoTotal += adj->distancia;
			}

			printf("%d -> ", grafo->lista[atual]->head->vertex);
		}
		printf("%d\n", grafo->lista[caminho[tamanhoCaminho - 1]]->head->vertex);

		printf("Peso total do caminho: %d\n", pesoTotal);
	}
	system("pause");
}

void floyd_warshall(int origem, int destino) {
	int **dist = (int **)malloc(grafo->numVertices * sizeof(int *));
	int **next = (int **)malloc(grafo->numVertices * sizeof(int *));

	for (int i = 0; i < grafo->numVertices; i++) {
		dist[i] = (int *)malloc(grafo->numVertices * sizeof(int));
		next[i] = (int *)malloc(grafo->numVertices * sizeof(int));
		for (int j = 0; j < grafo->numVertices; j++) {
			if (i == j) {
				dist[i][j] = 0;
			} else {
				dist[i][j] = INT_MAX;
			}
			next[i][j] = -1;
		}

		Vertice *atual = grafo->lista[i]->head;
		while (atual != NULL) {
			dist[i][atual->vertex] = atual->distancia;
			next[i][atual->vertex] = atual->vertex;
			atual = atual->prox;
		}
	}

	floydWarshall(dist, next);

	int tamanhoCaminho = 0;
	int *caminho = reconstruirCaminho(origem, destino, next, &tamanhoCaminho);
	imprimirFloyd(caminho, tamanhoCaminho, origem, destino);

	for (int i = 0; i < grafo->numVertices; i++) {
		free(dist[i]);
		free(next[i]);
	}
	free(dist);
	free(next);
	free(caminho);
}
