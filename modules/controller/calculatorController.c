#include "calculatorController.h"

#include <stdio.h>

#include "../types.h"

void calculaQuantidadeOnibusParada(int indiceParada) {
	int quantidade = 0;
	int onibus[10];
	int duplicado;

	for (int i = 0; i <= indices.indiceFrota; i++) {
		duplicado = 0;

		for (int k = 0; k < quantidade; k++) {
			if (onibus[k] == i) {
				duplicado = 1;
				break;
			}
		}

		if (duplicado) {
			continue;
		}

		for (int j = 0; j <= indices.indicePonto; j++) {
			if (percursos[i].rotas[indiceParada][j] != -1 || percursos[i].rotas[j][indiceParada] != -1) {
				onibus[quantidade] = i;
				quantidade++;
				break;
			}
		}
	}
	if (quantidade == 0) {
		printf("(Sem uso)\n");
	} else if (quantidade == 1) {
		printf("(Em uso por %s)\n", frota[onibus[0]].nome);
	} else {
		printf("(Em uso por ");
		for (int i = 0; i < quantidade; i++) {
			printf("%s", frota[onibus[i]].nome);
			if (i < quantidade - 1) {
				printf(", ");
			}
		}
		printf(")\n");
	}
}

void calculaQuantidadeOnibusRota(int rota) {
	int quantidade = 0;
	int onibus[100];
	int origem[100];
	int destino[100];
	int adicionados[100] = {0};

	for (int i = 0; i <= indices.indiceFrota; i++) {
		for (int j = 0; j < indices.indicePonto; j++) {
			for (int k = 0; k < indices.indicePonto; k++) {
				if (percursos[i].rotas[j][k] == rota) {
					onibus[quantidade] = i;
					origem[quantidade] = j;
					destino[quantidade] = k;
					quantidade++;
				}
			}
		}
	}

	if (quantidade == 0) {
		printf("(Sem uso)\n");
	} else if (quantidade == 1) {
		printf("(Em uso pelo onibus %s, passa pelos pontos '%s' - '%s')\n",
			   frota[onibus[0]].nome,
			   pontos[origem[0]].endereco,
			   pontos[destino[0]].endereco);
	} else {
		printf("(Em uso pelos onibus ");

		int primeiro = 1;
		for (int i = 0; i < quantidade; i++) {
			if (!adicionados[onibus[i]]) {
				if (!primeiro) {
					printf(", ");
				}
				printf("%s", frota[onibus[i]].nome);
				adicionados[onibus[i]] = 1;
				primeiro = 0;
			}
		}

		printf(" passando pelos pontos: ");

		for (int i = 0; i < quantidade; i++) {
			printf(" ('%s' - '%s')",
				   pontos[origem[i]].endereco,
				   pontos[destino[i]].endereco);
			if (i < quantidade - 1) {
				printf(", ");
			}
		}
		printf("\n");
	}
}

int rotasPorOnibus(Percurso percurso) {
	int total = 0;

	int i, j;

	int aux[MAX_SIZE];

	for (i = 0; i < MAX_SIZE; i++) {
		aux[i] = 0;
	}

	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			if (percurso.rotas[i][j] != -1) {
				aux[percurso.rotas[i][j]]++;
			}
		}
	}

	for (i = 0; i < MAX_SIZE; i++) {
		if (aux[i] > 0) {
			total++;
		}
	}

	return total;
}

int paradasPorOnibus(Percurso percurso) {
	int total = 0;

	int i, j;

	int aux[MAX_SIZE];

	for (i = 0; i < MAX_SIZE; i++) {
		aux[i] = 0;
	}

	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			if (percurso.rotas[i][j] != -1) {
				aux[i]++;
				aux[j]++;
			}
		}
	}

	for (i = 0; i < MAX_SIZE; i++) {
		if (aux[i] > 0) {
			total++;
		}
	}

	return total;
}

int arestasPorOnibus(Percurso percurso) {
	int total = 0;

	int i, j;

	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			if (percurso.rotas[i][j] != -1) {
				total++;
			}
		}
	}

	return total;
}