#include <stdio.h>

#include "../types.h"

void adicionarRota() {
	int i;

	if (indices.indiceRota + 1 > MAX_SIZE) {
		printf("A lista está cheia, remova uma rota antes de continuar\n\n");
		system("pause");
		return;
	}

	indices.indiceRota++;

	printf("\nRota %d:\n", indices.indiceRota + 1);

	printf("Digite o nome da rota: ");
	fflush(stdin);
	fgets(rotas[indices.indiceRota].nome, sizeof(rotas[indices.indiceRota].nome), stdin);
	rotas[indices.indiceRota].nome[strcspn(rotas[indices.indiceRota].nome, "\n")] = '\0';

	printf("Digite a distancia em km: ");
	while (scanf("%lf", &rotas[indices.indiceRota].distancia) != 1) {
		printf("Entrada invalida. Digite uma distancia valida: ");
		while (getchar() != '\n');
	}

	printf("Digite a duracao do percurso em minutos: ");
	while (scanf("%d", &rotas[indices.indiceRota].tempoPercurso) != 1) {
		printf("Entrada invalida. Digite uma duracao valida: ");
		while (getchar() != '\n');
	}

	printf("Rota adicionada com sucesso\n");
	system("pause");
}

void editarRota() {
	printf("Editar rota:\n");
	for (int i = 0; i <= indices.indiceRota; i++) {
		printf("%d) %s\n", (i + 1), rotas[i].nome);
	}

	printf("0) Voltar\n");

	int indice, i;

	printf("Informe o indice da rota a ser editada: ");
	do {
		scanf("%d", &indice);

		if (indice >= 0 && indice <= indices.indiceRota + 1)
			break;

		printf("Entrada invalida. Tente novamente: ");
		while (getchar() != '\n');
	} while (1);

	indice--;

	if (indice == -1) return;

	printf("Digite o nome da rota: ");
	fflush(stdin);
	fgets(rotas[indice].nome, sizeof(rotas[indice].nome), stdin);
	rotas[indice].nome[strcspn(rotas[indice].nome, "\n")] = '\0';

	printf("Digite a distancia em km: ");
	while (scanf("%lf", &rotas[indice].distancia) != 1) {
		printf("Entrada invalida. Digite uma distancia valida: ");
		while (getchar() != '\n');
	}

	printf("Digite a duracao do percurso em minutos: ");
	while (scanf("%d", &rotas[indice].tempoPercurso) != 1) {
		printf("Entrada invalida. Digite uma duracao valida: ");
		while (getchar() != '\n');
	}

	printf("Rota editada com sucesso\n");
	system("pause");
}

bool rota_em_uso(int indiceRota) {
	int i, j, k;

	for (i = 0; i < indices.indicePercurso; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			for (k = 0; k < MAX_SIZE; k++) {
				if (percursos[i].rotas[j][k] == indiceRota) {
					return true;
				}
			}
		}
	}

	return false;
}

void removerRota() {
	int indice;

	printf("Exclusao de rota:\n");
	for (int i = 0; i <= indices.indiceRota; i++) {
		printf("%d) %s\n", (i + 1), rotas[i].nome);
	}

	printf("0) Voltar\n");

	printf("Informe o indice da rota a ser removida: ");
	do {
		scanf("%d", &indice);

		while (getchar() != '\n');

		indice--;
		if (indice >= -1 && indice <= indices.indiceRota) {
			break;
		}

		printf("Entrada invalida. Digite um indice valido: ");
	} while (1);

	if (indice == -1) return;

	int i, j, k;

	if (rota_em_uso(indice)) {
		printf("A rota '%s' esta em uso e nao pode ser excluida.\n", rotas[indice].nome);
		return;
	}

	for (int i = indice; i < MAX_SIZE - 1; i++) {
		rotas[i] = rotas[i + 1];
	}

	strcpy(rotas[MAX_SIZE - 1].nome, "[A definir]");
	rotas[MAX_SIZE - 1].distancia = 0;
	rotas[MAX_SIZE - 1].tempoPercurso = 0;

	// Ajusta os índices das rotas na matriz de adjacências após a exclusão
	for (int i = 0; i < indices.indiceRota; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			for (int k = 0; k < MAX_SIZE; k++) {
				if (percursos[i].rotas[j][k] > indice) {
					percursos[i].rotas[j][k]--;
				}
			}
		}
	}

	indices.indiceRota--;

	printf("Rota removida com sucesso\n");
	system("pause");
}

void exibirRotas() {
	printf("Rotas:\n");

	for (int i = 0; i <= indices.indiceRota; i++) {
		printf("Indice: %d\n", i + 1);
		printf("Nome: %s\n", rotas[i].nome);
		printf("Distancia (km): %.2lf\n", rotas[i].distancia);
		printf("Tempo de Percurso (minutos): %d\n\n", rotas[i].tempoPercurso);
	}

	system("pause");
}