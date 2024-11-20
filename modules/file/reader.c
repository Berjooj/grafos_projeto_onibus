#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

Grafo* criar_grafo(int numVertices) {

    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->lista = (ListaAdj**)malloc(numVertices * sizeof(ListaAdj*));

    for (int i = 0; i < numVertices; i++) {
        grafo->lista[i] = (ListaAdj*)malloc(sizeof(ListaAdj));
        grafo->lista[i]->head = NULL;
    }

    return grafo;
}

void liberar_grafo(Grafo *grafo) {

    for (int i = 0; i < grafo->numVertices; i++) {
        Vertice *atual = grafo->lista[i]->head;
        while (atual != NULL) {
            Vertice *temp = atual;
            atual = atual->prox;
            free(temp);
        }
        free(grafo->lista[i]);
    }
    free(grafo->lista);
    free(grafo);
}

int buscar_vertice_por_endereco(Grafo *grafo, const char *endereco) {

    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->lista[i]->head != NULL && strcmp(grafo->lista[i]->head->endereco, endereco) == 0) {
            return i;
        }
    }
    return -1;
}

Vertice* adicionar_vertice(Grafo *grafo, const char *endereco, int vertex) {

    Vertice *novo_vertice = (Vertice*)malloc(sizeof(Vertice));
    novo_vertice->vertex = vertex;
    novo_vertice->distancia = 0;

    strncpy(novo_vertice->endereco, endereco, 150);
    novo_vertice->endereco[sizeof(novo_vertice->endereco) - 1] = '\0';

    novo_vertice->prox = NULL;

    if (grafo->lista[vertex]->head == NULL) {
        grafo->lista[vertex]->head = novo_vertice;
    } else {
        Vertice *atual = grafo->lista[vertex]->head;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_vertice;
    }

    return novo_vertice;
}

bool aresta_existe(Grafo *grafo, int origem, int destino) {

    Vertice *atual = grafo->lista[origem]->head;
    while (atual != NULL) {
        if (atual->vertex == destino) {
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

void adicionar_aresta(Grafo *grafo, int origem, int destino, int distancia) {
    if (origem == destino) {
        return;
    }

    if (!aresta_existe(grafo, origem, destino)) {
        Vertice *novo_vertice = (Vertice*)malloc(sizeof(Vertice));
        novo_vertice->vertex = destino;
        novo_vertice->distancia = distancia;
        novo_vertice->prox = NULL;

        strncpy(novo_vertice->endereco, grafo->lista[destino]->head->endereco, 150);
        novo_vertice->endereco[sizeof(novo_vertice->endereco) - 1] = '\0';

        if (grafo->lista[origem]->head == NULL) {
            grafo->lista[origem]->head = novo_vertice;
        } else {
            Vertice *atual = grafo->lista[origem]->head;
            while (atual->prox != NULL) {
                atual = atual->prox;
            }
            atual->prox = novo_vertice;
        }
    }
}

char* carregar_arquivo_json(const char *filename) {

    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *conteudo = (char*)malloc(tamanho + 1);
    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    return conteudo;
}

Grafo* parse_json_para_grafo(const char *json_string) {

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