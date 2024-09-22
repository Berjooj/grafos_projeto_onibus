#include <stdio.h>

#include "../types.h"

void calculaQuantidadeOnibusParada() {
	int indiceParada;
	int quantidade = 0;
	int onibus[100];
	limparTela();
	printf("\nPontos:\n");
	for (int i = 0; i <= indices.indicePonto; i++) {
		printf("Indice: %d\n", i + 1);
		printf("Endereco: %s\n\n", pontos[i].endereco);
	}
	do {
		printf("Escolha uma parada: ");
		scanf("%d", &indiceParada);
		while (getchar() != '\n');
		if (indiceParada > 0 && indiceParada <= indices.indicePonto) {
			break;
		}
		printf("Opcao invalida, tente novamente: ");
	} while (1);
	for (int i = 0; i <= indices.indiceFrota; i++) {
		for (int j = 0; j < indices.indicePonto; j++) {
			if (percursos[i].rotas[indiceParada - 1][j] != -1) {
				// printf("%d ", (percursos[i].rotas[indiceParada - 1][j]) + 1);
				onibus[quantidade] = i;
				quantidade++;
			};
		}
		// printf("\n");
	}
	if (quantidade == 0) {
		printf("Nenhum onibus passa por essa parada\n");
	} else if (quantidade == 1) {
		printf("\nApenas o onibus %s passa pela parada de indice %d\n", frota[onibus[0]].nome, indiceParada);
	} else {
		printf("Os onibus ");
		for (int i = 0; i < quantidade; i++) {
			printf("%s", frota[onibus[i]].nome);
			if (i < quantidade - 1) {
				printf(", ");
			}
		}
		printf(" passam pela parada de indice %d\n", indiceParada);
	}

	system("pause");
	limparTela();
}
void calculaQuantidadeOnibusRota() {
	int idOrigem, idDestino;
	int quantidade = 0;
	int onibus[100];
	limparTela();
	printf("\nRotas:\n");
	for (int i = 0; i <= indices.indicePonto; i++) {
		printf("%d. %s\n", i + 1, pontos[i].endereco);
	}

	printf("Escolha o ponto de ORIGEM: ");

	do {
		scanf("%d", &idOrigem);
		while (getchar() != '\n');

		if (idOrigem > 0 && idOrigem <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);

	printf("Escolha o ponto de DESTINO: ");
	do {
		scanf("%d", &idDestino);
		while (getchar() != '\n');

		if (idDestino > 0 && idDestino <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);
	for (int i = 0; i <= indices.indiceFrota; i++) {
		if (percursos[i].rotas[idOrigem - 1][idDestino - 1] != -1) {
			// printf("%d e %d", idOrigem - 1, idDestino - 1);
			onibus[quantidade] = i;
			quantidade++;
		}
	}
	if (quantidade == 0) {
		printf("Nenhum onibus passa por essa rota\n");
	} else if (quantidade == 1) {
		printf("\nApenas o onibus %s passa pela rota de origem '%s' - destino '%s'\n", frota[onibus[0]].nome, pontos[idOrigem - 1].endereco, pontos[idDestino - 1].endereco);
	} else {
		printf("Os onibus ");
		for (int i = 0; i < quantidade; i++) {
			printf("%s", frota[onibus[i]].nome);
			if (i < quantidade - 1) {
				printf(", ");
			}
		}
		printf(" passam pela rota de origem '%s' - destino '%s'\n", pontos[idOrigem - 1].endereco, pontos[idDestino - 1].endereco);
	}
	system("pause");
	limparTela();
}