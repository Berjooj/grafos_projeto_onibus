#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./file/exporter.c"
#include "./file/reader.c"
#include "./views/list.c"
#include "types.h"
#include "variables.c"

Grafo *criar_grafo(int numVertices) {
	Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
	grafo->numVertices = numVertices;
	grafo->numAresta = 0;
	grafo->lista = (ListaAdj **)malloc(numVertices * sizeof(ListaAdj *));

	for (int i = 0; i < numVertices; i++) {
		grafo->lista[i] = (ListaAdj *)malloc(sizeof(ListaAdj));
		grafo->lista[i]->head = NULL;
		grafo->lista[i]->visitado = false;
	}

	return grafo;
}

void liberar_grafo(Grafo *grafo) {
	for (int i = 0; i < grafo->numVertices; i++) {
		Vertice *atual = grafo->lista[i]->head;
		while (atual != NULL) {
			Vertice *temp = atual;
			atual = atual->prox;
			free(temp);
		}
		free(grafo->lista[i]);
	}
	free(grafo->lista);
	free(grafo);
}

int buscar_vertice_por_endereco(Grafo *grafo, const char *endereco) {
	for (int i = 0; i < grafo->numVertices; i++) {
		if (grafo->lista[i]->head != NULL && strcmp(grafo->lista[i]->head->endereco, endereco) == 0) {
			return i;
		}
	}
	return -1;
}

Vertice *adicionar_vertice(Grafo *grafo, const char *endereco, int vertex) {
	Vertice *novo_vertice = (Vertice *)malloc(sizeof(Vertice));
	novo_vertice->vertex = vertex;
	novo_vertice->distancia = 0;

	strncpy(novo_vertice->endereco, endereco, 150);
	novo_vertice->endereco[sizeof(novo_vertice->endereco) - 1] = '\0';

	novo_vertice->prox = NULL;

	if (grafo->lista[vertex]->head == NULL) {
		grafo->lista[vertex]->head = novo_vertice;
	} else {
		Vertice *atual = grafo->lista[vertex]->head;
		while (atual->prox != NULL) {
			atual = atual->prox;
		}
		atual->prox = novo_vertice;
	}

	return novo_vertice;
}

bool aresta_existe(Grafo *grafo, int origem, int destino) {
	Vertice *atual = grafo->lista[origem]->head;
	while (atual != NULL) {
		if (atual->vertex == destino) {
			return true;
		}
		atual = atual->prox;
	}
	return false;
}

void adicionar_aresta(Grafo *grafo, int origem, int destino, int distancia) {
	if (origem == destino) {
		return;
	}

	if (!aresta_existe(grafo, origem, destino)) {
		grafo->numAresta++;

		Vertice *novo_vertice = (Vertice *)malloc(sizeof(Vertice));
		novo_vertice->vertex = destino;
		novo_vertice->distancia = distancia;
		novo_vertice->prox = NULL;

		strncpy(novo_vertice->endereco, grafo->lista[destino]->head->endereco, 150);
		novo_vertice->endereco[sizeof(novo_vertice->endereco) - 1] = '\0';

		if (grafo->lista[origem]->head == NULL) {
			grafo->lista[origem]->head = novo_vertice;
		} else {
			Vertice *atual = grafo->lista[origem]->head;
			while (atual->prox != NULL) {
				atual = atual->prox;
			}
			atual->prox = novo_vertice;
		}
	}
}

void init(int lerArquivo, char *nome_arquivo) {
	const char *nome_arquivo_exportacao = "./output/resultado_grafo.json";

	printf("> Carregando arquivo...\n");

	char *json_string = carregar_arquivo_json(nome_arquivo);

	printf("> Arquivo carregado...\n");

	if (json_string) {
		printf("> Inicializando o grafo...\n");
		grafo = parse_json_para_grafo(json_string);
		printf("> Grafo inicializado com sucesso\n");
	}
}

void resetarVisita() {
	for (int i = 0; i < grafo->numVertices; i++) {
		grafo->lista[i]->visitado = false;
	}
}

void limparTela() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	return;
}