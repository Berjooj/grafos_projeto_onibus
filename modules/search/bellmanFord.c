#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int contadorVerticesVisitados;

bool relaxaAresta(int u, int v, int peso, int* dist, int* pred) {
	if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
		dist[v] = dist[u] + peso;
		pred[v] = u;
		return true;
	}

	return false;
}

void marcarCicloNegativo(int origem, bool* emCiclo, int* pred) {
	int atual = origem;
	do {
		emCiclo[atual] = true;
		atual = pred[atual];
	} while (atual != origem);
}

void exibirCiclosNegativos(bool* emCiclo, int numVertices) {
	printf("Caminhos envolvidos em ciclos de peso negativo:\n");
	for (int i = 0; i < numVertices; i++)
		if (emCiclo[i])
			printf("Parada %d\n", i);
}

int* buscaBellmanFord(int origem, int destino, int* tamanhoPercurso, int* distanciaFinal) {
	int* dist = malloc(grafo->numVertices * sizeof(int));
	int* pred = malloc(grafo->numVertices * sizeof(int));
	bool* emCiclo = calloc(grafo->numVertices, sizeof(bool));
	bool encontrouCicloNegativo = false;
	contadorVerticesVisitados = 0;

	// Inicializa distâncias e predecessores
	for (int i = 0; i < grafo->numVertices; i++) {
		dist[i] = INT_MAX;
		pred[i] = -1;
	}
	dist[origem] = 0;

	// Relaxa arestas
	for (int i = 1; i < grafo->numVertices; i++) {
		for (int u = 0; u < grafo->numVertices; u++) {
			if (emCiclo[u]) continue;
			Vertice* atual = grafo->lista[u]->head;
			contadorVerticesVisitados++;
			while (atual) {
				if (!emCiclo[atual->vertex]){
					relaxaAresta(u, atual->vertex, atual->distancia, dist, pred);
					contadorVerticesVisitados++;
				}
				atual = atual->prox;
			}
		}
	}

	// Detecta ciclos negativos
	for (int u = 0; u < grafo->numVertices; u++) {
		Vertice* atual = grafo->lista[u]->head;
		while (atual) {
			if (relaxaAresta(u, atual->vertex, atual->distancia, dist, pred)) {
				marcarCicloNegativo(atual->vertex, emCiclo, pred);
				encontrouCicloNegativo = true;
			}
			atual = atual->prox;
		}
	}

	// Exibe mensagem e detalhes sobre ciclos negativos, se encontrados
	if (encontrouCicloNegativo) {
		printf("Grafo contem ciclo de peso negativo, o caminho sera ignorado\n");
		exibirCiclosNegativos(emCiclo, grafo->numVertices);
	}

	// Verifica se o destino é acessível
	if (dist[destino] == INT_MAX || emCiclo[destino]) {
		free(dist);
		free(pred);
		free(emCiclo);
		return NULL;
	}

	// Reconstrói o caminho
	int* percurso = malloc(grafo->numVertices * sizeof(int));
	int atual = destino;
	*tamanhoPercurso = 0;

	while (atual != -1) {
		percurso[(*tamanhoPercurso)++] = atual;
		atual = pred[atual];
	}

	*distanciaFinal = dist[destino];

	free(dist);
	free(pred);
	free(emCiclo);
	return percurso;
}

// Coordena a execução do Bellman-Ford e imprime os resultados
void bellmanFord(int origem, int destino) {
	int tamanhoPercurso, distanciaFinal;
	int* percurso = buscaBellmanFord(origem, destino, &tamanhoPercurso, &distanciaFinal);

	if (!percurso) {
		printf("Nao existe caminho entre %s e %s.\n", grafo->lista[origem]->head->endereco, grafo->lista[destino]->head->endereco);
		system("pause");
		return;
	}

	printf("Caminho minimo de %d a %d:\n", origem, destino);

	for (int i = tamanhoPercurso - 1; i >= 0; i--)
		printf("%d ", percurso[i]);

	printf("\nDistancia total (caminho minimo): %d\n", distanciaFinal);
	printf("Total de vertices visitados: %d\n", contadorVerticesVisitados); // Exibe o contador

	free(percurso);
	system("pause");
}

void _bellmanFord(int origem, int destino) {
	int tamanhoPercurso, distanciaFinal;
	int* percurso = buscaBellmanFord(origem, destino, &tamanhoPercurso, &distanciaFinal);
	free(percurso);
	resetarVisita();
}