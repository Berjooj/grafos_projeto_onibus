#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./file/reader.c"
#include "./views/list.c"
#include "types.h"

void init(int lerArquivo) {
	int i, j, k;

	// Aloca os vetores e matrizes
	frota = (Onibus *)malloc(MAX_SIZE * sizeof(Onibus));
	pontos = (Ponto *)malloc(MAX_SIZE * sizeof(Ponto));
	rotas = (Rota *)malloc(MAX_SIZE * sizeof(Rota));
	percursos = (Percurso *)malloc(MAX_SIZE * sizeof(Percurso));

	for (i = 0; i < MAX_SIZE; i++) {
		percursos[i].rotas = malloc(MAX_SIZE * sizeof(int));

		for (j = 0; j < MAX_SIZE; j++) {
			percursos[i].rotas[j] = malloc(MAX_SIZE * sizeof(int));
		}
	}

	for (i = 0; i < MAX_SIZE; i++) {
		frota[i].autonomia = 0.0;
		frota[i].capacidadeCombustivel = 0.0;
		frota[i].lotacaoAtual = 0;
		frota[i].lotacaoMaxima = 0;
		strcpy(frota[i].nome, "[A definir]");

		pontos[i].lat = 0;
		pontos[i].lng = 0;
		pontos[i].eGaragem = false;
		strcpy(pontos[i].endereco, "[A definir]");

		strcpy(percursos[i].nome, "[A definir]");
		for (j = 0; j < MAX_SIZE; j++) {
			for (k = 0; k < MAX_SIZE; k++) {
				percursos[i].rotas[j][k] = -1;
				percursos[i].rotas[j][k] = -1;
			}
		}
	}

	if (lerArquivo == 1) {
		initArquivo();
	}
}
