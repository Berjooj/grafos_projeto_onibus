#include <sys/stat.h>
#include <sys/types.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

void criar_diretorio(const char *caminho) {
	struct stat st = {0};
	if (stat(caminho, &st) == -1) {
#ifdef _WIN32
		_mkdir(caminho);  // Windows
#else
		mkdir(caminho, 0700);  // Linux
#endif
	}
}

void exportar_grafo(Grafo *grafo, const char *nome_arquivo) {
	const char *diretorio = "./output";
	criar_diretorio(diretorio);

	cJSON *json = cJSON_CreateObject();
	cJSON *vertices = cJSON_CreateArray();
	cJSON *rotas = cJSON_CreateArray();

	for (int i = 0; i < grafo->numVertices; i++) {
		if (grafo->lista[i]->head != NULL) {
			cJSON *vertice = cJSON_CreateObject();
			cJSON_AddNumberToObject(vertice, "id", i);
			cJSON_AddStringToObject(vertice, "endereco", grafo->lista[i]->head->endereco);
			cJSON_AddItemToArray(vertices, vertice);
		}
	}
	cJSON_AddItemToObject(json, "vertices", vertices);

	for (int i = 0; i < grafo->numVertices; i++) {
		Vertice *atual = grafo->lista[i]->head;
		while (atual != NULL) {
			if (atual->prox != NULL) {
				cJSON *rota = cJSON_CreateObject();
				cJSON_AddNumberToObject(rota, "origem", i);
				cJSON_AddNumberToObject(rota, "destino", atual->vertex);
				cJSON_AddNumberToObject(rota, "distancia", atual->distancia);
				cJSON_AddItemToArray(rotas, rota);
			}
			atual = atual->prox;
		}
	}
	cJSON_AddItemToObject(json, "rotas", rotas);

	char *conteudo_json = cJSON_Print(json);
	FILE *arquivo = fopen(nome_arquivo, "w");
	if (arquivo) {
		fprintf(arquivo, "%s", conteudo_json);
		fclose(arquivo);
	} else {
		perror("Erro ao criar o arquivo de exportação");
	}

	cJSON_Delete(json);
	free(conteudo_json);
}