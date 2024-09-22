#include <stdio.h>

#include "../types.h"
#include "calculatorController.h"

void adicionarPonto() {
	int i;

	if (indices.indicePonto + 1 > MAX_SIZE) {
		printf("A lista está cheia, remova um ponto antes de continuar\n\n");
		system("pause");
		return;
	}

	indices.indicePonto++;

	printf("\nPonto %d:\n", indices.indicePonto + 1);

	printf("Digite o endereco do ponto: ");
	fflush(stdin);
	fgets(pontos[indices.indicePonto].endereco, sizeof(pontos[indices.indicePonto].endereco), stdin);
	pontos[indices.indicePonto].endereco[strcspn(pontos[indices.indicePonto].endereco, "\n")] = '\0';

	int eGaragem;
	printf("Este ponto e uma garagem? (1 para Sim, 0 para Nao): ");
	while (scanf("%d", &eGaragem) != 1 || (eGaragem != 0 && eGaragem != 1)) {
		printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
		while (getchar() != '\n');
	}
	pontos[indices.indicePonto].eGaragem = (eGaragem == 1);

	printf("Digite a latitude do ponto: ");
	while (scanf("%lf", &pontos[indices.indicePonto].lat) != 1) {
		printf("Entrada invalida. Digite a latitude do ponto: ");
		while (getchar() != '\n');
	}
	printf("Digite a longitude do ponto: ");
	while (scanf("%lf", &pontos[indices.indicePonto].lng) != 1) {
		printf("Entrada invalida. Digite a longitude do ponto: ");
		while (getchar() != '\n');
	}

	printf("Ponto adicionado com sucesso\n");
	system("pause");
}

void editarPonto() {
	printf("Editar ponto:\n");
	for (int i = 0; i <= indices.indicePonto; i++) {
		printf("%d) %s", (i + 1), pontos[i].endereco);
		calculaQuantidadeOnibusParada(i);
	}

	printf("0) Voltar\n");

	int indice, i;

	printf("Informe o indice do ponto a ser editado: ");
	do {
		scanf("%d", &indice);

		if (indice >= 0 && indice <= indices.indicePonto + 1)
			break;

		printf("Entrada invalida. Tente novamente: ");
		while (getchar() != '\n');
	} while (1);

	indice--;

	if (indice == -1) {
		return;
	}

	printf("Digite o endereco do ponto: ");
	fflush(stdin);
	fgets(pontos[indice].endereco, sizeof(pontos[indice].endereco), stdin);
	pontos[indice].endereco[strcspn(pontos[indice].endereco, "\n")] = '\0';

	int eGaragem;
	printf("Este ponto e uma garagem? (1 para Sim, 0 para Nao): ");
	while (scanf("%d", &eGaragem) != 1 || (eGaragem != 0 && eGaragem != 1)) {
		printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
		while (getchar() != '\n');
	}
	pontos[indice].eGaragem = (eGaragem == 1);

	printf("Digite a latitude do ponto: ");
	while (scanf("%lf", &pontos[indice].lat) != 1) {
		printf("Entrada invalida. Digite a latitude do ponto: ");
		while (getchar() != '\n');
	}
	printf("Digite a longitude do ponto: ");
	while (scanf("%lf", &pontos[indice].lng) != 1) {
		printf("Entrada invalida. Digite a longitude do ponto: ");
		while (getchar() != '\n');
	}

	printf("Ponto editado com sucesso\n");
	system("pause");
}

void removerPonto() {
	printf("Exclusao de ponto:\n");
	for (int i = 0; i <= indices.indicePonto; i++) {
		printf("%d) %s ", (i + 1), pontos[i].endereco);
		calculaQuantidadeOnibusParada(i);
	}

	printf("0) Voltar\n");

	int indice;

	printf("Informe o indice do ponto a ser removido: ");
	do {
		scanf("%d", &indice);

		while (getchar() != '\n');

		indice--;
		if (indice >= -1 && indice <= indices.indicePonto) {
			break;
		}

		printf("Entrada invalida. Digite o indice ponto: ");
	} while (1);

	if (indice == -1) return;

	int i, j, k;

	// Se é garagem e está vinculado a alguma rota, bloqueia a exclusão
	if (pontos[indice].eGaragem) {
		for (i = 0; i < MAX_SIZE; i++) {
			for (j = 0; j < MAX_SIZE; j++) {
				/**
				 * Percorre em cruz já que a regra diz que toda rota começa ou termina na garagem
				 */
				if (percursos[i].rotas[indice][j] != -1 || percursos[i].rotas[j][indice] != -1) {
					printf("Nao eh possivel excluir o vertice pois ele eh uma garagem, atualize o percurso e tente novamente\n");
					system("pause");
					return;
				}
			}
		}
	}

	/**
	 * 2hrs quebrando a cabeça :D
	 *
	 * Remove o vértice se utilizado em algum percurso setando o destino do anterior = próximo do vértice excluido
	 * Exemplo:
	 * A -> B -> C
	 *
	 * Removendo o B resultaria em:
	 * A -> C
	 */
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			// Verifica se existe uma aresta preenchida
			if (percursos[i].rotas[j][indice] != -1) {
				// Puxa os destinos do ponto excluido para o ponto que tinha o nó excluido como destino
				for (int k = 0; k < MAX_SIZE; k++) {
					if (percursos[i].rotas[indice][k] != -1) {
						// Atualiza os filhos
						percursos[i].rotas[j][k] = percursos[i].rotas[j][indice];

						// Limpa o destino
						percursos[i].rotas[j][indice] = -1;
					}
				}
			}
		}

		// Limpar as arestas do ponto que foi removido
		for (int k = 0; k < MAX_SIZE; k++) {
			percursos[i].rotas[indice][k] = -1;
		}
	}

	// Puxa todos os índices para trás já que um foi excluido
	for (int i = indice; i < MAX_SIZE - 1; i++) {
		pontos[i] = pontos[i + 1];
	}

	// Redefine o último ponto
	strcpy(pontos[MAX_SIZE - 1].endereco, "[A definir]");
	pontos[MAX_SIZE - 1].eGaragem = false;
	pontos[MAX_SIZE - 1].lat = 0;
	pontos[MAX_SIZE - 1].lng = 0;

	// Agora redefine os índices em TODAS as matrizes
	for (int i = 0; i < MAX_SIZE; i++) {
		// Puxa todas as colunas uma posição pra trás
		for (int j = 0; j < MAX_SIZE; j++) {
			for (int k = indice; k < MAX_SIZE - 1; k++) {
				percursos[i].rotas[j][k] = percursos[i].rotas[j][k + 1];
			}

			// Redefine a última coluna com -1
			percursos[i].rotas[j][MAX_SIZE - 1] = -1;
		}

		// Puxa todas as linhas uma posição pra trás
		for (int j = indice; j < MAX_SIZE - 1; j++) {
			for (int k = 0; k < MAX_SIZE; k++) {
				percursos[i].rotas[j][k] = percursos[i].rotas[j + 1][k];
			}
		}

		// Redefine a última linha
		for (int k = 0; k < MAX_SIZE; k++) {
			percursos[i].rotas[MAX_SIZE - 1][k] = -1;
		}
	}

	indices.indicePonto--;

	printf("Ponto removido com sucesso\n");
	system("pause");
}

void exibirPontos() {
	printf("\nPontos:\n");

	for (int i = 0; i <= indices.indicePonto; i++) {
		char garagem[] = "Nao";

		if (pontos[i].eGaragem == 1) {
			strcpy(garagem, "Sim");
		}

		printf("Indice: %d\n", i + 1);
		printf("Endereco: %s\nLatitude: %.2f\nLongitude: %.2f\nGaragem: %s\n", pontos[i].endereco, pontos[i].lat, pontos[i].lng, garagem);
		calculaQuantidadeOnibusParada(i);
		printf("\n");
	}

	system("pause");
}