#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

void buscaDijkstra(int origem, int destino, int** distancias, int** anteriores) {
	int indiceParadaAtual;

	*distancias = (int*)malloc(grafo->numVertices * sizeof(int));
	*anteriores = (int*)malloc(grafo->numVertices * sizeof(int));

	for (int i = 0; i < grafo->numVertices; i++) {
		(*distancias)[i] = INT_MAX;
		(*anteriores)[i] = -1;
	}

	(*distancias)[origem] = 0;

	while (!grafo->lista[destino]->visitado) {
		indiceParadaAtual = -1;
		int menorDistancia = INT_MAX;

		// Seleciona o próximo vértice com menor distância
		for (int i = 0; i < grafo->numVertices; i++) {
			if (!grafo->lista[i]->visitado && (*distancias)[i] < menorDistancia) {
				indiceParadaAtual = i;
				menorDistancia = (*distancias)[i];
			}
		}

		// Sem caminho, break
		if (indiceParadaAtual == -1) break;

		grafo->lista[indiceParadaAtual]->visitado = true;

		// Se chegou no destino, break
		if (indiceParadaAtual == destino) break;

		// Relaxa as arestas do vértice indiceParadaAtual
		Vertice* adj = grafo->lista[indiceParadaAtual]->head;
		while (adj) {
			if (!grafo->lista[adj->vertex]->visitado && (*distancias)[indiceParadaAtual] + adj->distancia < (*distancias)[adj->vertex]) {
				(*distancias)[adj->vertex] = (*distancias)[indiceParadaAtual] + adj->distancia;
				(*anteriores)[adj->vertex] = indiceParadaAtual;
			}
			adj = adj->prox;
		}
	}
}

void dijkstra(int origem, int destino) {
	// Inicializa as distâncias e o conjunto de vértices abertos
	int* distancias;
	int* anteriores;

	buscaDijkstra(origem, destino, &distancias, &anteriores);

	// Se a distancia for o máximo do int, quer dizer que não encontrou nada
	if (distancias[destino] == INT_MAX) {
		free(distancias);
		free(anteriores);

		printf("Nao existe caminho entre %s e %s.\n", grafo->lista[origem]->head->endereco, grafo->lista[destino]->head->endereco);
		system("pause");
		return;
	}

	printf("Caminho encontrado entre %d e %d: ", origem, destino);

	// Reconstrói o caminho em ordem correta
	int parada = destino;
	int caminho[grafo->numVertices];
	int indice = 0;

	while (parada != -1) {
		caminho[indice++] = parada;
		parada = anteriores[parada];
	}

	// Imprime o caminho na ordem certa
	for (int i = indice - 1; i >= 0; i--)
		printf("%d ", caminho[i]);

	printf("\nDistancia total (caminho minimo): %d\n", distancias[destino]);

	free(distancias);
	free(anteriores);

	system("pause");
}