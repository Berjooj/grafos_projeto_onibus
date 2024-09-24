#include "reader.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

void parseOnibus(cJSON *onibusArray) {
	int i;
	int qtd = cJSON_GetArraySize(onibusArray);

	for (i = 0; i < qtd; i++) {
		if (qtd > MAX_SIZE) {
			printf("Onibus nao incluido, matriz sem espaco!\n");
			break;
		}

		cJSON *onibusItem = cJSON_GetArrayItem(onibusArray, i);
		cJSON *nome = cJSON_GetObjectItem(onibusItem, "nome");
		cJSON *lotacaoMaxima = cJSON_GetObjectItem(onibusItem, "lotacaoMaxima");
		cJSON *lotacaoAtual = cJSON_GetObjectItem(onibusItem, "lotacaoAtual");
		cJSON *capacidadeCombustivel = cJSON_GetObjectItem(onibusItem, "capacidadeCombustivel");
		cJSON *autonomia = cJSON_GetObjectItem(onibusItem, "autonomia");

		strcpy(frota[i].nome, nome->valuestring);
		frota[i].lotacaoMaxima = lotacaoMaxima->valueint;
		frota[i].lotacaoAtual = lotacaoAtual->valueint;
		frota[i].capacidadeCombustivel = (float)capacidadeCombustivel->valuedouble;
		frota[i].autonomia = (float)autonomia->valuedouble;

		indices.indiceFrota = i;
	}
}

void parseRotas(cJSON *rotasArray) {
	int i;
	int qtd = cJSON_GetArraySize(rotasArray);

	for (i = 0; i < qtd; i++) {
		if (qtd > MAX_SIZE) {
			printf("Rota nao incluida, matriz sem espaco!\n");
			break;
		}

		cJSON *rotaItem = cJSON_GetArrayItem(rotasArray, i);
		cJSON *nome = cJSON_GetObjectItem(rotaItem, "nome");
		cJSON *distancia = cJSON_GetObjectItem(rotaItem, "distancia");
		cJSON *tempoPercurso = cJSON_GetObjectItem(rotaItem, "tempoPercurso");

		strcpy(rotas[i].nome, nome->valuestring);
		rotas[i].distancia = distancia->valuedouble;
		rotas[i].tempoPercurso = tempoPercurso->valueint;

		indices.indiceRota = i;
	}
}

void parsePontos(cJSON *pontosArray) {
	int i;
	int qtd = cJSON_GetArraySize(pontosArray);

	for (i = 0; i < qtd; i++) {
		if (qtd > MAX_SIZE) {
			printf("Ponto nao incluido, matriz sem espaco!\n");
			break;
		}

		cJSON *pontoItem = cJSON_GetArrayItem(pontosArray, i);
		cJSON *endereco = cJSON_GetObjectItem(pontoItem, "endereco");
		cJSON *eGaragem = cJSON_GetObjectItem(pontoItem, "eGaragem");
		cJSON *lat = cJSON_GetObjectItem(pontoItem, "lat");
		cJSON *lng = cJSON_GetObjectItem(pontoItem, "lng");

		strcpy(pontos[i].endereco, endereco->valuestring);
		pontos[i].eGaragem = eGaragem->valueint;
		pontos[i].lat = lat->valuedouble;
		pontos[i].lng = lng->valuedouble;

		indices.indicePonto = i;
	}
}

void parsePercursos(cJSON *percursoArray) {
	int i, j, k;
	int qtd = cJSON_GetArraySize(percursoArray);

	for (i = 0; i < qtd; i++) {
		if (qtd > MAX_SIZE) {
			printf("Percurso nao incluido, matriz sem espaco!\n");
			break;
		}

		cJSON *percursoItem = cJSON_GetArrayItem(percursoArray, i);
		cJSON *linha = cJSON_GetObjectItem(percursoItem, "linha");
		cJSON *rotasJson = cJSON_GetObjectItem(percursoItem, "rotas");

		int indiceOnibus = -1;

		for (j = 0; j <= indices.indiceFrota; j++) {
			if (strcmp(frota[j].nome, linha->valuestring) == 0) {
				indiceOnibus = j;
				break;
			}
		}

		if (indiceOnibus == -1) {
			printf("Nao foi possivel carregar o percurso '%s'\n", linha->valuestring);
			return;
		}

		int qtdRotas = cJSON_GetArraySize(rotasJson);
		for (j = 0; j < qtdRotas; j++) {
			cJSON *rota = cJSON_GetArrayItem(rotasJson, j);
			cJSON *origem = cJSON_GetObjectItem(rota, "origem");
			cJSON *destino = cJSON_GetObjectItem(rota, "destino");
			cJSON *_rota = cJSON_GetObjectItem(rota, "rota");

			int indiceOrigem = -1, indiceDestino = -1, indiceRota = -1;

			// Procurando o índice da origem no array de pontos
			for (k = 0; k < MAX_SIZE; k++) {
				if (strcmp(pontos[k].endereco, origem->valuestring) == 0)
					indiceOrigem = k;

				if (strcmp(pontos[k].endereco, destino->valuestring) == 0)
					indiceDestino = k;

				if (strcmp(rotas[k].nome, _rota->valuestring) == 0)
					indiceRota = k;
			}

			// Atualizando a matriz de adjacência com os índices das pontos
			if (indiceOrigem != -1 && indiceDestino != -1 && indiceRota != -1)
				percursos[indiceOnibus].rotas[indiceOrigem][indiceDestino] = indiceRota;
			else
				printf("Erro: Rota nao encontrada (%s -> %s, %s)\n", origem->valuestring, destino->valuestring, _rota->valuestring);
		}

		indices.indicePercurso = i;
	}
}

void initArquivo() {
	FILE *arquivo = fopen("./config/data.json", "r");

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo JSON.\n");
		return;
	}

	// Converte o arquivo em texto para objeto da lib
	fseek(arquivo, 0, SEEK_END);
	long tamanhoArquivo = ftell(arquivo);

	fseek(arquivo, 0, SEEK_SET);
	char *data = malloc(tamanhoArquivo + 1);

	fread(data, 1, tamanhoArquivo, arquivo);
	fclose(arquivo);

	cJSON *json = cJSON_Parse(data);
	if (!json) {
		printf("Erro ao analisar o JSON.\n");
		return;
	}

	// Converte o JSON para o array de struct
	cJSON *onibusArray = cJSON_GetObjectItem(json, "onibus");
	parseOnibus(onibusArray);

	cJSON *rotasArray = cJSON_GetObjectItem(json, "rotas");
	parseRotas(rotasArray);

	cJSON *pontosArray = cJSON_GetObjectItem(json, "pontos");
	parsePontos(pontosArray);

	cJSON *percursoArray = cJSON_GetObjectItem(json, "percurso");
	parsePercursos(percursoArray);

	// Libera a memória
	cJSON_Delete(json);
	free(data);
}
