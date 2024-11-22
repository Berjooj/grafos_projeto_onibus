#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

int *buscaLargura(int origem, int destino, int *tamanhoCaminho) {
    int *fila = (int *)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    bool *visitado = (bool *)malloc(grafo->numVertices * sizeof(bool));
    int *pai = (int *)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++) {
        visitado[i] = false;
        pai[i] = -1;
    }

    visitado[origem] = true;
    fila[tras++] = origem;

    while (frente < tras) {
        int atual = fila[frente++];

        if (atual == destino) {
            break;
        }

        Vertice *verticeAtual = grafo->lista[atual]->head;
        while (verticeAtual) {
            int v = verticeAtual->vertex;
            if (!visitado[v]) {
                visitado[v] = true;
                fila[tras++] = v;
                pai[v] = atual;
            }
            verticeAtual = verticeAtual->prox;
        }
    }

    if (!visitado[destino]) {
        free(fila);
        free(visitado);
        free(pai);
        *tamanhoCaminho = 0;
        return NULL;
    }

    int *caminho = (int *)malloc(grafo->numVertices * sizeof(int));
    int indiceCaminho = 0;

    for (int v = destino; v != -1; v = pai[v]) {
        caminho[indiceCaminho++] = v;
    }

    free(fila);
    free(visitado);
    free(pai);

    *tamanhoCaminho = indiceCaminho;
    return caminho;
}

void imprimirCaminho(int *caminho, int tamanhoCaminho, int origem, int destino) {
    if (caminho == NULL || tamanhoCaminho == 0) {
        printf("Nao existe caminho entre %s e %s.\n",
            grafo->lista[origem]->head->endereco,
            grafo->lista[destino]->head->endereco);
    } else {
        printf("Caminho encontrado entre %d e %d: ", origem, destino);
        for (int i = tamanhoCaminho - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    }
    system("pause");
}

void largura(int origem, int destino) {
    int tamanhoCaminho = 0;
    int *caminho = buscaLargura(origem, destino, &tamanhoCaminho);
    imprimirCaminho(caminho, tamanhoCaminho, origem, destino);
    free(caminho);
}