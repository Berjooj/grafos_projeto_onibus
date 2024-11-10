#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>

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
	
    char diretorio[256];
    strncpy(diretorio, nome_arquivo, sizeof(diretorio));
    char *fim_linha = strrchr(diretorio, '/');
    if (fim_linha != NULL) {
        *fim_linha = '\0';
        criar_diretorio(diretorio);
    }

    cJSON *json_grafo = cJSON_CreateObject();
    cJSON *json_vertices = cJSON_CreateArray();

    for (int i = 0; i < grafo->quant_vertices; i++) {
        cJSON *json_no = cJSON_CreateObject();
        cJSON_AddStringToObject(json_no, "endereco", grafo->vertices[i].endereco);

        cJSON *json_arestas = cJSON_CreateArray();
        Aresta *aresta = grafo->vertices[i].lista_adj;

        while (aresta) {
            cJSON *json_aresta = cJSON_CreateObject();
            cJSON_AddStringToObject(json_aresta, "destino", grafo->vertices[aresta->destino].endereco);
            cJSON_AddNumberToObject(json_aresta, "distancia", aresta->distancia);

            cJSON_AddItemToArray(json_arestas, json_aresta);
            aresta = aresta->proxima;
        }

        cJSON_AddItemToObject(json_no, "adjacentes", json_arestas);
        cJSON_AddItemToArray(json_vertices, json_no);
    }

    cJSON_AddItemToObject(json_grafo, "vertices", json_vertices);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo) {
        char *json_string = cJSON_Print(json_grafo);
        fprintf(arquivo, "%s\n", json_string);
        fclose(arquivo);
        free(json_string);
    } else {
        perror("Erro ao abrir o arquivo para exportação");
    }

    cJSON_Delete(json_grafo);
}