#include "reader.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

Grafo* criar_grafo(int capacidade) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->vertices = (Vertice *)malloc(sizeof(Vertice) * capacidade);
    grafo->quant_vertices = 0;
    grafo->capacidade = capacidade;
    return grafo;
}

void liberar_grafo(Grafo *grafo) {
    for (int i = 0; i < grafo->quant_vertices; i++) {
        Aresta *aresta = grafo->vertices[i].lista_adj;
        while (aresta) {
            Aresta *temp = aresta;
            aresta = aresta->proxima;
            free(temp);
        }
    }
    free(grafo->vertices);
    free(grafo);
}

int encontrar_indice_vertice(Grafo *grafo, const char *endereco) {

    for (int i = 0; i < grafo->quant_vertices; i++) {
        if (strcmp(grafo->vertices[i].endereco, endereco) == 0) {
            return i;
        }
    }
    return -1;
}

int adicionar_vertice(Grafo *grafo, const char *endereco) {

    int indice = encontrar_indice_vertice(grafo, endereco);
    if (indice == -1) {
        if (grafo->quant_vertices == grafo->capacidade) {
            grafo->capacidade *= 2;
            grafo->vertices = (Vertice *)realloc(grafo->vertices, sizeof(Vertice) * grafo->capacidade);
        }
        strncpy(grafo->vertices[grafo->quant_vertices].endereco, endereco, 150);
        grafo->vertices[grafo->quant_vertices].lista_adj = NULL;
        return grafo->quant_vertices++;
    }
    return indice;
}

int aresta_existe(Grafo *grafo, int indice_origem, int indice_destino) {

    Aresta *aresta = grafo->vertices[indice_origem].lista_adj;
    while (aresta) {
        if (aresta->destino == indice_destino) {
            return 1;
        }
        aresta = aresta->proxima;
    }
    return 0;
}

void adicionar_aresta(Grafo *grafo, const char *origem, const char *destino, int distancia) {

    int indice_origem = adicionar_vertice(grafo, origem);
    int indice_destino = adicionar_vertice(grafo, destino);

    if (aresta_existe(grafo, indice_origem, indice_destino)) {
        return;
    }

    Aresta *nova_aresta = (Aresta *)malloc(sizeof(Aresta));
    if (!nova_aresta) {
        fprintf(stderr, "Erro ao alocar memória para a aresta.\n");
        exit(EXIT_FAILURE);
    }

    nova_aresta->destino = indice_destino;
    nova_aresta->distancia = distancia;
    nova_aresta->proxima = grafo->vertices[indice_origem].lista_adj;
    grafo->vertices[indice_origem].lista_adj = nova_aresta;
}

char* carregar_arquivo_json(const char *nome_arquivo) {

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *conteudo = (char *)malloc(tamanho_arquivo + 1);
    if (!conteudo) {
        fprintf(stderr, "Erro ao alocar memória\n");
        fclose(arquivo);
        return NULL;
    }

    size_t bytesLidos = fread(conteudo, 1, tamanho_arquivo, arquivo);
    conteudo[bytesLidos] = '\0';

    fclose(arquivo);
    return conteudo;
}

Grafo* parse_json_para_grafo(const char *json_string) {

    Grafo *grafo = criar_grafo(10);
    cJSON *json = cJSON_Parse(json_string);

    if (!json) {
        fprintf(stderr, "Erro ao ler JSON\n");
        exit(EXIT_FAILURE);
    }

    cJSON *pontos_json = cJSON_GetObjectItemCaseSensitive(json, "pontos");
    cJSON *ponto;

    cJSON_ArrayForEach(ponto, pontos_json) {
        const char *endereco = cJSON_GetObjectItemCaseSensitive(ponto, "endereco")->valuestring;
        adicionar_vertice(grafo, endereco);
    }

    cJSON *rotas_json = cJSON_GetObjectItemCaseSensitive(json, "rotas");
    cJSON *rota;

    cJSON_ArrayForEach(rota, rotas_json) {
		
        const char *origem = cJSON_GetObjectItemCaseSensitive(rota, "origem")->valuestring;
        const char *destino = cJSON_GetObjectItemCaseSensitive(rota, "destino")->valuestring;
        int distancia = cJSON_GetObjectItemCaseSensitive(rota, "distancia")->valueint;

        adicionar_aresta(grafo, origem, destino, distancia);
    }

    cJSON_Delete(json);
    return grafo;
}