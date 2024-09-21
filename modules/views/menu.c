#include "itinerary.c"
#include "points.c"
// #include "../views/routeController.c"

void menu() {
	int opcao;

	do {
		opcao = -1;
		printf("\nMenu:\n");
		printf("1. Gerenciar Pontos\n");
		printf("2. Gerenciar Rotas\n");
		printf("3. Gerenciar Onibus\n");
		printf("4. Definir Roteiro\n");
		printf("5. ??\n");
		printf("6. ??\n");
		printf("7. ??\n");
		printf("8. ??\n");
		printf("9. ??\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				gerenciarPontos();
				break;
			case 2:
				// cadastrarRotas();
				break;
			// case 3:
			// 	exibirPontos();
			// 	break;
			case 4:
				definirRoteiro();
				break;
			// case 5:
			// 	listarMatriz();
			// 	break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("\n\nOpcao invalida!");
				break;
		}
	} while (opcao != 0);
}