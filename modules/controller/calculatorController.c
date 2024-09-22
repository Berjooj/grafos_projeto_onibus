#include "../types.h"
#include "itineraryController.h"

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