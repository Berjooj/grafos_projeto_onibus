#include "itinerary.c"
#include "points.c"
#include "routes.c"
#include "bus.c"
#include "../file/exporter.c"

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
		printf("7. Exportar JSON\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		switch (opcao) {
			case 1:
				gerenciarPontos();
				break;
			case 2:
				gerenciarRotas();
				break;
			case 3:
				gerenciarOnibus();
				break;
			case 4:
				definirRoteiro();
				break;
			case 7:
				exportarJson();
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("\n\nOpcao invalida!");
				break;
		}
	} while (opcao != 0);
}