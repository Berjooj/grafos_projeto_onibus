#include <stdlib.h>

#include "../controller/routeController.c"

void gerenciarRotas() {
	int opcao;

	do {
		limparTela();

		printf("\nGerenciar Rotas:\n");
		printf("1. Adicionar rota\n");
		printf("2. Editar rota\n");
		printf("3. Listar rotas\n");
		printf("4. Remover rota\n");
		printf("0. Voltar\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				adicionarRota();
				break;
			case 2:
				editarRota();
				break;
			case 3:
				exibirRotas();
				break;
			case 4:
				removerRota();
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