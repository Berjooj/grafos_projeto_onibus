#include "./../functions.h"
#include "./../search/bellmanFord.c"
#include "./../search/bfs.c"
#include "./../search/buscaBenchmark.c"
#include "./../search/dfs.c"
#include "./../search/dijkstra.c"
#include "./../search/floyd.c"

void menu() {
	int opcao;

	do {
		opcao = -1;
		printf("\nTotal de paradas: %d\n", grafo->numVertices);
		printf("Total de arestas: %d\n", grafo->numAresta);
		printf("\nMenu:\n");
		printf("1. Busca em profundidade\n");
		printf("2. Busca em largura\n");
		printf("3. Dijkstra\n");
		printf("4. Floyd\n");
		printf("5. Bellman-Ford\n");
		printf("6. Benchmark\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n');

		/**
		 * > Arquivo completo
		 * Legenda pra facilitar a vida:
		 * 1009 - Av Baltazar De Oliveira Garcia318 - Agronomia // Triângulo da assis
		 * 1119 - Avenida Manoel Elias 2000 // UniRitter FAPA
		 * 2075 - Avenida Julio De Castilhos 647 Centro Historico // Rodoviária
		 * 6664 - Rodoviaria De Montenegro
		 */
		// int origem = 6664, destino = 1119;

		/**
		 * > Arquivo resumido
		 * Legenda pra facilitar a vida:
		 * 22 - Av Baltazar De Oliveira Garcia318 - Agronomia // Triângulo da assis
		 * 7 - Avenida Manoel Elias 2000 // UniRitter FAPA
		 */
		int origem = 22, destino = 7;

		printf("Digite o indice da origem: ");
		scanf("%d", &origem);

		printf("Digite o indice do destino: ");
		scanf("%d", &destino);

		switch (opcao) {
			case 1:
				profundidade(origem, destino);
				break;
			case 2:
				largura(origem, destino);
				break;
			case 3:
				dijkstra(origem, destino);
				break;
			case 4:
				floyd_warshall(origem, destino);
				break;
			case 5:
				bellmanFord(origem, destino);
				break;
			case 6:
				buscaBenchmark(origem, destino);
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("\n\nOpcao invalida!");
				break;
		}

		resetarVisita();
	} while (opcao != 0);
}