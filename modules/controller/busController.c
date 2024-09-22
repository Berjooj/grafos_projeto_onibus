#include <stdio.h>

#include "../types.h"

void adicionarOnibus() {
	int i;

	if (indices.indiceFrota + 1 > MAX_SIZE) {
		printf("A lista está cheia, remova um onibus antes de continuar\n\n");
		system("pause");
		return;
	}

	indices.indiceFrota++;

	printf("\nOnibus %d:\n", indices.indiceFrota + 1);

	printf("Digite o nome do onibus: ");
	fflush(stdin);
	fgets(frota[indices.indiceFrota].nome, sizeof(frota[indices.indiceFrota].nome), stdin);
	frota[indices.indiceFrota].nome[strcspn(frota[indices.indiceFrota].nome, "\n")] = '\0';

	printf("Digite a capacidade do tanque em litros: ");
	while (scanf("%f", &frota[indices.indiceFrota].capacidadeCombustivel) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	printf("Quantos kms por litro o onibus anda? ");
	while (scanf("%f", &frota[indices.indiceFrota].autonomia) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	printf("Digite a lotacao maxima: ");
	while (scanf("%d", &frota[indices.indiceFrota].lotacaoMaxima) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	frota[indices.indiceFrota].lotacaoAtual = 0;

	printf("Onibus adicionado com sucesso\n");
	system("pause");
}

void editarOnibus() {
	int indice;

	printf("Edicao de onibus:\n");
	for (int i = 0; i <= indices.indiceFrota; i++) {
		printf("%d) %s\n", (i + 1), frota[i].nome);
	}

	printf("0) Voltar\n");

	printf("Informe o indice do onibus a ser editado: ");
	do {
		scanf("%d", &indice);

		while (getchar() != '\n');

		indice--;
		if (indice >= -1 && indice <= indices.indiceFrota) {
			break;
		}

		printf("Entrada invalida. Digite um indice valido: ");
	} while (1);

	if (indice == -1) return;

	int i, j, k;

	printf("Digite o nome do onibus: ");
	fflush(stdin);
	fgets(frota[indices.indiceFrota].nome, sizeof(frota[indices.indiceFrota].nome), stdin);
	frota[indices.indiceFrota].nome[strcspn(frota[indices.indiceFrota].nome, "\n")] = '\0';

	printf("Digite a capacidade do tanque em litros: ");
	while (scanf("%f", &frota[indices.indiceFrota].capacidadeCombustivel) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	printf("Quantos kms por litro o onibus anda? ");
	while (scanf("%f", &frota[indices.indiceFrota].autonomia) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	printf("Digite a lotacao maxima: ");
	while (scanf("%d", &frota[indices.indiceFrota].lotacaoMaxima) != 1) {
		printf("Entrada invalida. Digite um valor valido: ");
		while (getchar() != '\n');
	}

	frota[indices.indiceFrota].lotacaoAtual = 0;

	printf("Onibus editado com sucesso\n");
	system("pause");
}

void removerOnibus() {
	int indice;

	printf("Exclusao de onibus:\n");
	for (int i = 0; i <= indices.indiceFrota; i++) {
		printf("%d) %s\n", (i + 1), frota[i].nome);
	}

	printf("0) Voltar\n");

	printf("Informe o indice do onibus a ser excluido: ");
	do {
		scanf("%d", &indice);

		while (getchar() != '\n');

		indice--;
		if (indice >= -1 && indice <= indices.indiceFrota) {
			break;
		}

		printf("Entrada invalida. Digite um indice valido: ");
	} while (1);

	if (indice == -1) return;

	int i, j;

	for (i = indice; i < indices.indiceFrota; i++) {
		percursos[i] = percursos[i + 1];
		frota[i] = frota[i + 1];
	}

	strcpy(frota[indices.indiceFrota].nome, "[A definir]");
	frota[indices.indiceFrota].autonomia = 0;
	frota[indices.indiceFrota].capacidadeCombustivel = 0;
	frota[indices.indiceFrota].lotacaoAtual = 0;
	frota[indices.indiceFrota].lotacaoMaxima = 0;

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			percursos[indices.indiceFrota].rotas[i][j] = -1;
		}
	}

	indices.indiceFrota--;

	printf("Onibus removido com sucesso\n");
	system("pause");
}

void exibirFrota() {
	printf("Frota:\n");

	for (int i = 0; i <= indices.indiceFrota; i++) {
		printf("Indice: %d\n", i + 1);
		printf("Nome: %s\n", frota[i].nome);
		printf("Lotacao maxima: %d\n", frota[i].lotacaoMaxima);
		printf("Capacidade do tanque (litros): %.2lf\n", frota[i].capacidadeCombustivel);
		printf("Autonomia (km/l): %.2lf\n\n", frota[i].autonomia);
	}

	system("pause");
}