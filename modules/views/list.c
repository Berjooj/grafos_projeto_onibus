#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"

void listarPontos() {
	printf("\nPontos:\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("Endereco: %s\nlatitude: %.2f\nlongitude: %.2f\nGaragem: %d\n\n", pontos[i].endereco, pontos[i].lat, pontos[i].lng, pontos[i].eGaragem);
	}
}

void exibirMatriz(int indicePercurso) {
	if (indicePercurso < 0 || indicePercurso >= MAX_SIZE) {
		printf("Indice inválido (%d)\n", indicePercurso);
		return;
	}

	printf("%s\n", percursos[indicePercurso].nome);

	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			printf("%3d ", percursos[indicePercurso].rotas[i][j]);
		}
		printf("\n");
	}
}