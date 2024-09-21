#include <stdio.h>
#include <stdlib.h>

#include "./modules/functions.c"

int main() {
	do {
		printf("Digite o numero de pontos: ");
		scanf("%d", &MAX_SIZE);
		while (getchar() != '\n');

		if (MAX_SIZE > 0)
			break;
		else
			printf("Digite um valor valido!\n");
	} while (1);

	init(1);

	// menu();

	// freePontos();
	// freeMatrizDeRotas();

	listarPontos();

	exibirMatriz(0);

	printf("\n\nPrecione qualquer tecla para sair...\n");
	getchar();
	return 0;
}
