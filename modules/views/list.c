#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"

void exibirMatriz(int indicePercurso) {
	if (indicePercurso < 0 || indicePercurso >= MAX_SIZE) {
		printf("Indice inválido (%d)\n", indicePercurso);
		return;
	}

	printf("%s\n", frota[indicePercurso].nome);

	int i, j;
	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			printf("%3d ", percursos[indicePercurso].rotas[i][j]);
		}
		printf("\n");
	}
}