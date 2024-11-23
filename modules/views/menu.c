#include "./../functions.h"
#include "./../search/dfs.c"
#include "./../search/bfs.c"
#include "./../search/dijkstra.c"
#include "./../search/floyd.c"
#include "./../search/bellmanFord.c"

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
		 * Legenda pra facilitar a vida:
		 * 1009 - Av Baltazar De Oliveira Garcia318 - Agronomia // Triângulo da assis
		 * 1119 - Avenida Manoel Elias 2000 // UniRitter FAPA
		 * 2075 - Avenida Julio De Castilhos 647 Centro Historico // Rodoviária
		 * 6664 - Rodoviaria De Montenegro
		 */
		switch (opcao) {
			case 1:
				profundidade(6664, 1119);
				break;
			case 2:
				largura(6664, 1119);
				break;
			case 3:
				dijkstra(6664, 1119);
				break;
			case 4:
				floyd_warshall(6664,1119);
				break;
			case 5:
				bellmanFord(6664, 1119);
				break;
			// case 6:
			// 	buscaBenchmark();
			// 	break;
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