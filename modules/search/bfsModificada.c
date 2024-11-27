#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <windows.h>

#include "../functions.h"
#include "../types.h"
#include "../variables.c"

int contadorVerticesVisitados;

void resetarVisitadosModif() {
	for (int i = 0; i < grafo->numVertices; i++) {
		grafo->lista[i]->visitado = false;
	}
	contadorVerticesVisitados = 0;
}

void criarDiretorios(const char *caminho) {
    DIR *dir = opendir(caminho);
    if (!dir) {
        _mkdir(caminho);
    } else {
        closedir(dir);
    }
}

void gerarCaminhoResult(char *caminho, char *horario, const char *nomeFuncao) {
    strcpy(caminho, "result");
    criarDiretorios(caminho);

    sprintf(caminho, "%s\\%s", caminho, horario);
    criarDiretorios(caminho);

    sprintf(caminho, "%s\\%s", caminho, nomeFuncao);
    criarDiretorios(caminho);
}

void exportarCaminhosParaArquivo(int **todosCaminhos, int numCaminhos, int origem, int destino, int *tamanhosCaminhos, int tamanhoOtimo, int *caminhoOtimo) {
    SYSTEMTIME st;
	GetLocalTime(&st);
	char horario[400];
	sprintf(horario, "%02d%02d%04d%02d%02d%02d",
			st.wDay, st.wMonth, st.wYear,
			st.wHour, st.wMinute, st.wSecond);

	char caminhoLog[256];

	gerarCaminhoResult(caminhoLog, horario, "larguraModificada");

	char arquivoLog[512];
	sprintf(arquivoLog, "%s\\log.txt", caminhoLog);
	FILE *arquivo = fopen(arquivoLog, "w");

	if (!arquivo) {
		perror("Erro ao criar arquivo de log");
		return;
	}

    if (numCaminhos == 0) {
        fprintf(arquivo, "Nao existe caminho entre %s e %s.\n",
                grafo->lista[origem]->head->endereco, grafo->lista[destino]->head->endereco);
    } else {
        fprintf(arquivo, "Foram encontrados %d caminhos entre %d e %d:\n", numCaminhos, origem, destino);
        for (int i = 0; i < numCaminhos; i++) {
            fprintf(arquivo, "\nCaminho %d: ", i + 1);
            for (int j = 0; j < tamanhosCaminhos[i]; j++) {
                if (j == tamanhosCaminhos[i] - 1){
                    fprintf(arquivo, "%d", todosCaminhos[i][j]);
                } else {
                    fprintf(arquivo, "%d, ", todosCaminhos[i][j]);
                }
            }
            fprintf(arquivo, "\n");
        }
        // Exibindo o caminho ótimo
        fprintf(arquivo, "\nCaminho ótimo (menor número de arestas): ");
        for (int i = 0; i < tamanhoOtimo; i++) {
            if (i == tamanhoOtimo - 1) {
                fprintf(arquivo, "%d", caminhoOtimo[i]);
            } else {
                fprintf(arquivo, "%d, ", caminhoOtimo[i]);
            }
        }
        fprintf(arquivo, "\n");
        fprintf(arquivo, "Quantidade de vertices visitados: %d\n", contadorVerticesVisitados);
    }
    fclose(arquivo);

	printf("Log gerado em: result\\%s\\larguraModificada\\log.txt\n", horario);
	system("pause");
}

void encontrarCaminhosBFS(int atual, int destino, int *caminhoAtual, int tamanhoAtual, int ***todosCaminhos, int **tamanhosCaminhos, int *numCaminhos) {
    grafo->lista[atual]->visitado = true;
    contadorVerticesVisitados++;
    caminhoAtual[tamanhoAtual++] = atual;

    if (atual == destino) {
        *todosCaminhos = (int **)realloc(*todosCaminhos, (*numCaminhos + 1) * sizeof(int *));
        *tamanhosCaminhos = (int *)realloc(*tamanhosCaminhos, (*numCaminhos + 1) * sizeof(int));

        (*todosCaminhos)[*numCaminhos] = (int *)malloc(tamanhoAtual * sizeof(int));
        memcpy((*todosCaminhos)[*numCaminhos], caminhoAtual, tamanhoAtual * sizeof(int));

        (*tamanhosCaminhos)[*numCaminhos] = tamanhoAtual;
        (*numCaminhos)++;
    } else {
        Vertice *verticeAtual = grafo->lista[atual]->head;
        while (verticeAtual) {
            int v = verticeAtual->vertex;
            if (!grafo->lista[v]->visitado) {
                encontrarCaminhosBFS(v, destino, caminhoAtual, tamanhoAtual, todosCaminhos, tamanhosCaminhos, numCaminhos);
            }
            verticeAtual = verticeAtual->prox;
        }
    }

    grafo->lista[atual]->visitado = false;
}

int **encontrarTodosCaminhos(int origem, int destino, int *numCaminhos, int **tamanhosCaminhos) {
    resetarVisitadosModif();
    int *caminhoAtual = malloc(grafo->numVertices * sizeof(int));
    int **todosCaminhos = NULL;
    *tamanhosCaminhos = NULL;
    *numCaminhos = 0;

    encontrarCaminhosBFS(origem, destino, caminhoAtual, 0, &todosCaminhos, tamanhosCaminhos, numCaminhos);

    free(caminhoAtual);
    return todosCaminhos;
}

void larguraTodosCaminhos(int origem, int destino) {
    int numCaminhos = 0;
    int *tamanhosCaminhos = NULL;
    int **todosCaminhos = encontrarTodosCaminhos(origem, destino, &numCaminhos, &tamanhosCaminhos);

    // Encontrar o caminho ótimo (menor número de arestas)
    int *caminhoOtimo = NULL;
    int tamanhoOtimo = -1;
    for (int i = 0; i < numCaminhos; i++) {
        if (tamanhoOtimo == -1 || tamanhosCaminhos[i] < tamanhoOtimo) {
            tamanhoOtimo = tamanhosCaminhos[i];
            caminhoOtimo = todosCaminhos[i];
        }
    }

    // Exporta os caminhos para o arquivo
    exportarCaminhosParaArquivo(todosCaminhos, numCaminhos, origem, destino, tamanhosCaminhos, tamanhoOtimo, caminhoOtimo);

    // Libera a memória
    for (int i = 0; i < numCaminhos; i++) free(todosCaminhos[i]);
    free(todosCaminhos);
    free(tamanhosCaminhos);
}

void _larguraTodosCaminhos(int origem, int destino) {
    int numCaminhos = 0, *tamanhosCaminhos = NULL;

    // Calcula todos os caminhos
    int **todosCaminhos = encontrarTodosCaminhos(origem, destino, &numCaminhos, &tamanhosCaminhos);

    // Encontra o caminho ótimo
    int *caminhoOtimo = NULL, tamanhoOtimo = -1;
    for (int i = 0; i < numCaminhos; i++) {
        if (tamanhoOtimo == -1 || tamanhosCaminhos[i] < tamanhoOtimo) {
            tamanhoOtimo = tamanhosCaminhos[i];
            caminhoOtimo = todosCaminhos[i];
        }
    }

    // Exporta os caminhos para o arquivo
    // exportarCaminhosParaArquivo(todosCaminhos, numCaminhos, origem, destino, tamanhosCaminhos, tamanhoOtimo, caminhoOtimo);

    // Libera a memória
    for (int i = 0; i < numCaminhos; i++) free(todosCaminhos[i]);
    free(todosCaminhos);
    free(tamanhosCaminhos);
}