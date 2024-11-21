#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

char *carregar_arquivo_json(const char *filename) {
	FILE *arquivo = fopen(filename, "r");
	if (!arquivo) {
		perror("Erro ao abrir o arquivo");
		return NULL;
	}

	fseek(arquivo, 0, SEEK_END);
	long tamanho = ftell(arquivo);
	fseek(arquivo, 0, SEEK_SET);

	char *conteudo = (char *)malloc(tamanho + 1);
	fread(conteudo, 1, tamanho, arquivo);
	conteudo[tamanho] = '\0';
	fclose(arquivo);

	return conteudo;
}

Grafo *parse_json_para_grafo(const char *json_string) {
	cJSON *json = cJSON_Parse(json_string);
	if (!json) {
		printf("Erro ao parsear o JSON\n");
		return NULL;
	}

	cJSON *vertices = cJSON_GetObjectItem(json, "vertices");
	if (!vertices || !cJSON_IsArray(vertices)) {
		printf("Erro: 'vertices' não encontrado ou não é um array\n");
		cJSON_Delete(json);
		return NULL;
	}

	int numVertices = cJSON_GetArraySize(vertices);
	Grafo *grafo = criar_grafo(numVertices);

	cJSON *vertice;
	int id = 0;
	cJSON_ArrayForEach(vertice, vertices) {
		const char *endereco = cJSON_GetObjectItem(vertice, "endereco")->valuestring;
		adicionar_vertice(grafo, endereco, id++);
	}

	cJSON *rotas = cJSON_GetObjectItem(json, "rotas");
	if (rotas && cJSON_IsArray(rotas)) {
		cJSON *rota;
		cJSON_ArrayForEach(rota, rotas) {
			int origem_id = cJSON_GetObjectItem(rota, "origem")->valueint;
			int destino_id = cJSON_GetObjectItem(rota, "destino")->valueint;
			int distancia = cJSON_GetObjectItem(rota, "distancia")->valueint;

			if (origem_id != destino_id) {
				adicionar_aresta(grafo, origem_id, destino_id, distancia);
			}
		}
	}

	cJSON_Delete(json);
	return grafo;
}