#include <stdio.h>

#include "../types.h"

void preenchePontos() {
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("\nPonto %d:\n", i + 1);

		printf("Digite o endereco do ponto: ");
		fgets(pontos[i].endereco, sizeof(pontos[i].endereco), stdin);
		pontos[i].endereco[strcspn(pontos[i].endereco, "\n")] = '\0';

		int eGaragem;
		printf("Este ponto e uma garagem? (1 para Sim, 0 para Nao): ");
		while (scanf("%d", &eGaragem) != 1 || (eGaragem != 0 && eGaragem != 1)) {
			printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
			while (getchar() != '\n');
		}
		pontos[i].eGaragem = (eGaragem == 1);

		printf("Digite a latitude do ponto: ");
		while (scanf("%lf", &pontos[i].lat) != 1) {
			printf("Entrada invalida. Digite a latitude do ponto: ");
			while (getchar() != '\n');
		}
		printf("Digite a longitude do ponto: ");
		while (scanf("%lf", &pontos[i].lng) != 1) {
			printf("Entrada invalida. Digite a longitude do ponto: ");
			while (getchar() != '\n');
		}

		while (getchar() != '\n');
	}
}