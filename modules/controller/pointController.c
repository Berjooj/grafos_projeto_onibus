#include <stdio.h>

#include "../types.h"

void adicionarPonto() {
	int i;

	if (indices.indicePonto + 1 > MAX_SIZE) {
		printf("A lista está cheia, remova um ponto antes de continuar\n\n");
		system("pause");
		return;
	}

	indices.indicePonto++;

	printf("\nPonto %d:\n", indices.indicePonto + 1);

	printf("Digite o endereco do ponto: ");
	fgets(pontos[indices.indicePonto].endereco, sizeof(pontos[indices.indicePonto].endereco), stdin);
	pontos[indices.indicePonto].endereco[strcspn(pontos[indices.indicePonto].endereco, "\n")] = '\0';

	int eGaragem;
	printf("Este ponto e uma garagem? (1 para Sim, 0 para Nao): ");
	while (scanf("%d", &eGaragem) != 1 || (eGaragem != 0 && eGaragem != 1)) {
		printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
		while (getchar() != '\n');
	}
	pontos[indices.indicePonto].eGaragem = (eGaragem == 1);

	printf("Digite a latitude do ponto: ");
	while (scanf("%lf", &pontos[indices.indicePonto].lat) != 1) {
		printf("Entrada invalida. Digite a latitude do ponto: ");
		while (getchar() != '\n');
	}
	printf("Digite a longitude do ponto: ");
	while (scanf("%lf", &pontos[indices.indicePonto].lng) != 1) {
		printf("Entrada invalida. Digite a longitude do ponto: ");
		while (getchar() != '\n');
	}

	system("pause");
}

void removerPonto() {
	printf("Exclusão de ponto: ");
	for (int i = 0; i < indices.indicePonto; i++) {
		printf("%d) %s", (i + 1), pontos[i].endereco);
	}

	int indice;

	printf("Informe o indice do ponto a ser removido: ");
	do {
		scanf("%d", &indice);

		if (indice >= 0 || indice <= indices.indicePonto)
			break;

		printf("Entrada invalida. Digite a latitude do ponto: ");
		while (getchar() != '\n');
	} while (1);
}

void exibirPontos() {
	printf("\nPontos:\n");

	for (int i = 0; i < MAX_SIZE; i++) {
		printf("Endereco: %s\nLatitude: %.2f\nLongitude: %.2f\nGaragem: %d\n\n", pontos[i].endereco, pontos[i].lat, pontos[i].lng, pontos[i].eGaragem);
	}

	system("pause");
}