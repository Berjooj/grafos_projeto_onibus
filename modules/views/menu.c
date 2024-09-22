#include "bus.c"
#include "itinerary.c"
#include "points.c"
#include "routes.c"

void menu() {
	int opcao;

	do {
		opcao = -1;
		printf("\nMenu:\n");
		printf("1. Gerenciar Pontos\n");
		printf("2. Gerenciar Rotas\n");
		printf("3. Gerenciar Onibus\n");
		printf("4. Definir Roteiro\n");
		printf("5. Validar quantos onibus passam pela parada\n");
		printf("6. Validar quantos onibus utilizam a mesma rota\n");
		printf("7. Validar quantas rotas sao utilizadas por uma linha de onibus\n");
		printf("8. Validar quantar paradas existem em um roteiro do onibus\n");
		printf("9. Exportar em Json\n");
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
			case 5:
				// calculaQuantidadeOnibusParada();
				break;
			case 6:
				// calculaQuantidadeOnibusRota();
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
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