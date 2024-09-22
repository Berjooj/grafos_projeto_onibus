#include "itinerary.h"

#include <stdlib.h>

#include "../controller/itineraryController.c"

void definirRoteiro()
{
	int indiceOnibus, i;

	limparTela();
	do
	{
		printf("Selecionar Roteiro:\n");

		for (i = 0; i <= indices.indiceFrota; i++)
		{
			printf("%d. %s\n", i + 1, frota[i].nome);
		}

		printf("0. Voltar\n");
		printf("Escolha uma opcao: ");

		do
		{
			scanf("%d", &indiceOnibus);
			while (getchar() != '\n')
				;

			if (indiceOnibus >= 0 && indiceOnibus <= MAX_SIZE)
			{
				break;
			}

			printf("Opcao invalida, tente novamente: ");
		} while (1);

		if (indiceOnibus == 0)
		{
			limparTela();
			break;
		}

		menuOnibusRoteiro(indiceOnibus);
	} while (1);
}

void menuOnibusRoteiro(int indiceOnibus)
{
	int opcao, i;
	indiceOnibus--;

	Percurso percursoTemp;
	percursoTemp.rotas = malloc(MAX_SIZE * sizeof(int *));

	for (int i = 0; i < MAX_SIZE; i++)
	{
		percursoTemp.rotas[i] = malloc(MAX_SIZE * sizeof(int));

		// Copiar os dados da rota original
		for (int j = 0; j < MAX_SIZE; j++)
		{
			percursoTemp.rotas[i][j] = percursos[indiceOnibus].rotas[i][j];
		}
	}

	do
	{
		opcao = -1;
		limparTela();

		printf("[Linha %s]\n", frota[indiceOnibus].nome);

		printf("1. Adicionar rota\n");
		printf("2. Remover rota\n");
		printf("3. Exibir roteiro\n");
		printf("4. Exibir matriz\n");
		printf("9. Salvar e voltar\n");
		printf("0. Voltar sem salvar\n");
		printf("Escolha uma opcao: ");

		scanf("%d", &opcao);
		while (getchar() != '\n')
			;

		switch (opcao)
		{
		case 1:
			adicionarPontoRota(&percursoTemp);
			break;
		case 2:
			removerPontoRota(&percursoTemp);
			break;
		case 3:
			exibirPontoRota(&percursoTemp);
			break;
		case 4:
			exibirMatrizPontoRota(&percursoTemp);
			break;
		case 9:
			// TODO:
			salvarPontoRota(&percursoTemp, indiceOnibus);
			break;
		case 0:
			limparTela();
			break;
		default:
			printf("Opcao invalida! Tente novamente: ");
			break;
		}

		if (opcao == 9 || opcao == 0)
		{
			break;
		}
	} while (1);
}