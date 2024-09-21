#include <stdlib.h>

#include "../controller/pointController.c"

void gerenciarPontos() {
	int opcao;

	do {
		printf("\nMenu:\n");
		printf("1. Adicionar ponto\n");
		printf("2. Remover ponto\n");
		printf("3. Listar pontos\n");
		printf("0. Voltar\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				adicionarPonto();
				break;
			case 2:
				removerPonto();
				break;
			case 3:
				exibirPontos();
				break;
			case 0:
				break;
			default:
				printf("Opcao invalida! Tente novamente.\n");
				break;
		}

		limparTela();
	} while (opcao != 0);
}