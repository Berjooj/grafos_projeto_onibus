#include "itineraryController.h"

#include "../types.h"
#include "calculatorController.c"

void adicionarPontoRota(Percurso *percursoTemp) {
	int idOrigem, idDestino, idRota, i;

	for (i = 0; i <= indices.indicePonto; i++) {
		printf("%d. %s\n", i + 1, pontos[i].endereco);
	}

	printf("Escolha o ponto de ORIGEM: ");

	do {
		scanf("%d", &idOrigem);
		while (getchar() != '\n');

		if (idOrigem > 0 && idOrigem <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);

	printf("Escolha o ponto de DESTINO: ");
	do {
		scanf("%d", &idDestino);
		while (getchar() != '\n');

		if (idDestino > 0 && idDestino <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);

	if (idOrigem == idDestino) {
		printf("\nRota invalida, Origem precisa ser diferente de Destino\n");
	} else {
		for (i = 0; i <= indices.indiceRota; i++) {
			if (strcmp(rotas[i].nome, "[A definir]") == 0) {
				continue;
			}

			printf("%d. %s (%.2lf km)\n", i + 1, rotas[i].nome, rotas[i].distancia);
		}

		printf("Escolha a rota do percurso: ");
		do {
			scanf("%d", &idRota);
			while (getchar() != '\n');

			if (idRota > 0 && idRota <= MAX_SIZE) {
				break;
			}
			printf("Opcao invalida, tente novamente: ");
		} while (1);
		if (percursoTemp->rotas[idOrigem - 1][idDestino - 1] != -1) {
			printf("\nJa existe uma rota com essa Origem e Destino, sobrescrevendo rota\n");
			percursoTemp->rotas[idOrigem - 1][idDestino - 1] = idRota - 1;
		} else {
			percursoTemp->rotas[idOrigem - 1][idDestino - 1] = idRota - 1;
			printf("\nRota adicionada com sucesso!\n");
		}
	}
	system("pause");
}

void removerPontoRota(Percurso *percursoTemp) {
	int idOrigem, idDestino, idRota, i;

	for (i = 0; i <= indices.indicePonto; i++) {
		printf("%d. %s\n", i + 1, pontos[i].endereco);
	}

	printf("Escolha o ponto de ORIGEM: ");

	do {
		scanf("%d", &idOrigem);
		while (getchar() != '\n');

		if (idOrigem > 0 && idOrigem <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);

	printf("Escolha o ponto de DESTINO: ");
	do {
		scanf("%d", &idDestino);
		while (getchar() != '\n');

		if (idDestino > 0 && idDestino <= MAX_SIZE) {
			break;
		}

		printf("Opcao invalida, tente novamente: ");
	} while (1);
	percursoTemp->rotas[idOrigem - 1][idDestino - 1] = -1;
	// for (int i = 0; i < MAX_SIZE; i++)
	// {
	// 	if (percursoTemp->rotas[idOrigem][i] != -1 && i < idDestino)
	// 	{
	// 		percursoTemp->rotas[idOrigem - 1][i] = percursoTemp->rotas[idOrigem - 1][idDestino - 1];
	// 		percursoTemp->rotas[idOrigem - 1][idDestino - 1] = -1;
	// 		percursoTemp->rotas[idOrigem][i] = -1;
	// 		break;
	// 	}
	// 	else if (percursoTemp->rotas[idOrigem][i] != -1 && i > idDestino - 1)
	// 	{
	// 		printf("%d e %d", idOrigem, i);
	// 		percursoTemp->rotas[idOrigem - 1][i] = percursoTemp->rotas[idOrigem][i];
	// 		percursoTemp->rotas[idOrigem][i] = -1;
	// 		percursoTemp->rotas[idOrigem - 1][idDestino - 1] = -1;
	// 		break;
	// 	}
	// 	else
	// 	{
	// 		for (int j = 0; j < idDestino; j++)
	// 		{
	// 			if (percursoTemp->rotas[idOrigem - 2][j] != -1)
	// 			{
	// 				percursoTemp->rotas[idOrigem - 1][j] = percursoTemp->rotas[idOrigem - 2][j];
	// 				percursoTemp->rotas[idOrigem - 2][j] = -1;
	// 				percursoTemp->rotas[idOrigem - 1][idDestino - 1] = -1;
	// 				break;
	// 			}
	// 		}
	// 	}
	system("pause");
}

void exibirPontoRota(Percurso *percursoTemp) {
	int i, j;

	bool exibiu = false;

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			if (percursoTemp->rotas[i][j] != -1) {
				exibiu = true;
				printf(
					"| Rota: %s (%.2lf km)\n| Origem: %s (%.4lf, %.4lf)\n| Destino: %s (%.4lf, %.4lf)\n\n",
					rotas[percursoTemp->rotas[i][j]].nome,
					rotas[percursoTemp->rotas[i][j]].distancia,
					pontos[i].endereco,
					pontos[i].lat,
					pontos[i].lng,
					pontos[j].endereco,
					pontos[j].lat,
					pontos[j].lng);
			}
		}
	}

	if (!exibiu) {
		printf("\nRoteiro nao definido\n");
	}

	system("pause");
}

void exibirMatrizPontoRota(Percurso *percursoTemp) {
	int i, j;

	printf("    | ");
	for (j = 0; j <= indices.indicePonto; j++) {
		printf("%3d", j + 1);
	}
	printf("\n------------------------\n");

	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			if (j == 0) {
				printf("%3d | ", i + 1);
			}

			printf("%3d", percursoTemp->rotas[i][j] + 1);
		}
		printf("\n");
	}

	system("pause");
}

void limparRoteiro(Percurso *percursoTemp) {
	int i, j;
	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			percursoTemp->rotas[i][j] = -1;
		}
	}

	printf("Roteiro limpo\n");
	system("pause");
}

void copiarRoteiro(Percurso *percursoTemp, int idOnibus) {
	int indiceOnibus, i, j;

	bool erro = false;

	do {
		limparTela();
		printf("Selecione um roteiro para copiar:\n");

		for (i = 0; i <= indices.indiceFrota; i++) {
			if (i == idOnibus) {
				continue;
			}

			printf("%d. %s\n", i + 1, frota[i].nome);
		}

		printf("0. Voltar\n");

		if (!erro) {
			printf("Escolha uma opcao: ");
		} else {
			printf("Opcao invalida, tente novamente: ");
		}

		do {
			scanf("%d", &indiceOnibus);
			while (getchar() != '\n');

			if (indiceOnibus >= 0 && indiceOnibus <= MAX_SIZE) {
				break;
			}
		} while (1);

		indiceOnibus--;
		if (indiceOnibus != idOnibus) {
			limparTela();
			break;
		}

		erro = true;
	} while (1);

	for (i = 0; i <= indices.indicePonto; i++) {
		for (j = 0; j <= indices.indicePonto; j++) {
			percursoTemp->rotas[i][j] = percursos[indiceOnibus].rotas[i][j];
		}
	}

	printf("Roteiro clonado com sucesso\n");
	system("pause");
}

void salvarPontoRota(Percurso *percursoTemp, int indiceOnibus) {
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			percursos[indiceOnibus].rotas[i][j] = percursoTemp->rotas[i][j];
		}
	}
}

// bool validarPontoRota(Percurso *percursoTemp)
// {
// 	for (int i = 0; i < MAX_SIZE; i++)
// 	{
// 		for (int j = 0; j < MAX_SIZE; j++)
// 		{
// 			if (percursoTemp->rotas[i][j != -1])
// 			{
// 				for (int k = 0; k < MAX_SIZE; k++)
// 				{
// 					percursoTemp->rotas[j][k]
// 				}
// 			}
// 		}
// 	}
// }