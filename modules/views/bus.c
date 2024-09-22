#include <stdlib.h>

#include "../controller/busController.c"

void gerenciarOnibus() {
	int opcao;

	do {
		limparTela();

		printf("\nGerenciar Onibus:\n");
		printf("1. Adicionar onibus\n");
		printf("2. Editar onibus\n");
		printf("3. Listar frota\n");
		printf("4. Remover onibus\n");
		printf("0. Voltar\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				adicionarOnibus();
				break;
			case 2:
				editarOnibus();
				break;
			case 3:
				exibirFrota();
				break;
			case 4:
				removerOnibus();
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