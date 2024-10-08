#include <stdlib.h>

#include "../controller/pointController.c"

void gerenciarPontos() {
	int opcao;

	do {
		limparTela();

		printf("\nGerenciar Pontos:\n");
		printf("1. Adicionar ponto\n");
		printf("2. Editar ponto\n");
		printf("3. Listar pontos\n");
		printf("4. Remover ponto\n");
		printf("0. Voltar\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				adicionarPonto();
				break;
			case 2:
				editarPonto();
				break;
			case 3:
				exibirPontos();
				break;
			case 4:
				removerPonto();
				break;
			case 0:
				limparTela();
				break;
			default:
				printf("Opcao invalida! Tente novamente.\n");
				break;
		}
	} while (opcao != 0);
}