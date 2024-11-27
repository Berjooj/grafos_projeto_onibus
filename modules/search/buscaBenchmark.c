#include <direct.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <windows.h>

#include "buscas.h"

double medirTempo(void (*funcao)(int, int), int origem, int destino) {
	LARGE_INTEGER inicio, fim, frequencia;

	QueryPerformanceFrequency(&frequencia);
	QueryPerformanceCounter(&inicio);

	funcao(origem, destino);

	QueryPerformanceCounter(&fim);

	return (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;
}

void ordenar(double *tempos, int tamanho) {
	for (int i = 0; i < tamanho - 1; i++) {
		for (int j = 0; j < tamanho - i - 1; j++) {
			if (tempos[j] > tempos[j + 1]) {
				double temp = tempos[j];
				tempos[j] = tempos[j + 1];
				tempos[j + 1] = temp;
			}
		}
	}
}

double calcularMedia(double *tempos, int tamanho) {
	double soma = 0.0;

	for (int i = 0; i < tamanho; i++)
		soma += tempos[i];

	return soma / tamanho;
}

void gerarCaminhoLog(char *caminho, char *horario, const char *nomeFuncao) {
	sprintf(caminho, "logs");

	DIR *dir = opendir(caminho);

	if (!dir)
		_mkdir(caminho);

	sprintf(caminho, "%s\\%s", caminho, horario);

	DIR *dirHorario = opendir(caminho);

	if (!dirHorario)
		_mkdir(caminho);

	sprintf(caminho, "%s\\%s", caminho, nomeFuncao);

	DIR *dirFuncao = opendir(caminho);

	if (!dirFuncao)
		_mkdir(caminho);
}

void executar(void (*funcao)(int, int), const char *nomeFuncao, char *horario, int origem, int destino, int tamanho) {
	double tempos[tamanho];
	char caminhoLog[256];
	int execucaoAtual, i;

	gerarCaminhoLog(caminhoLog, horario, nomeFuncao);

	char arquivoLog[512];
	sprintf(arquivoLog, "%s\\log.txt", caminhoLog);
	FILE *arquivo = fopen(arquivoLog, "w");

	if (!arquivo) {
		perror("Erro ao criar arquivo de log");
		return;
	}

	for (execucaoAtual = 1; execucaoAtual <= tamanho; execucaoAtual++) {
		limparTela();
		printf("Executando o algoritmo %s...\n", nomeFuncao);
		printf("Progresso %d/%d (%d%%)...\n", execucaoAtual, tamanho, (execucaoAtual * tamanho) / tamanho);

		tempos[execucaoAtual - 1] = medirTempo(funcao, origem, destino);
	}

	ordenar(tempos, tamanho);

	fprintf(arquivo, "%.10f|%.10f,%.10f,%.10f,%.10f,%.10f\n",
			calcularMedia(tempos, 5),
			tempos[0], tempos[1], tempos[2], tempos[3], tempos[4]);

	fprintf(arquivo, "%.10f|%.10f,%.10f,%.10f,%.10f,%.10f\n",
			calcularMedia(&tempos[tamanho - 5], 5),
			tempos[tamanho - 5], tempos[tamanho - 4],
			tempos[tamanho - 3], tempos[tamanho - 2],
			tempos[tamanho - 1]);

	fprintf(arquivo, "%.10f|", calcularMedia(&tempos[5], 90));
	for (i = 5; i < tamanho - 5; i++) {
		fprintf(arquivo, "%.10f", tempos[i]);
		if (i < tamanho - 6)
			fprintf(arquivo, ";");
	}
	fprintf(arquivo, "\n");

	fclose(arquivo);
}

void buscaBenchmark(int origem, int destino) {
	SYSTEMTIME st;
	GetLocalTime(&st);

	char horario[400];

	sprintf(horario, "%02d%02d%04d%02d%02d%02d",
			st.wDay, st.wMonth, st.wYear,
			st.wHour, st.wMinute, st.wSecond);

	int tamanho = 100;

	executar(_profundidade, "profundidade", horario, origem, destino, tamanho);
	executar(_largura, "largura", horario, origem, destino, tamanho);
	executar(_larguraTodosCaminhos, "larguraModif", horario, origem, destino, tamanho);
	executar(_dijkstra, "dijkstra", horario, origem, destino, tamanho);
	executar(_bellmanFord, "bellmanFord", horario, origem, destino, tamanho);
	executar(_floyd_warshall, "floyd_warshall", horario, origem, destino, tamanho);

	printf("Log gerado em: logs\\%s\\profundidade\\log.txt\n", horario);
	printf("Log gerado em: logs\\%s\\largura\\log.txt\n", horario);
	printf("Log gerado em: logs\\%s\\dijkstra\\log.txt\n", horario);
	printf("Log gerado em: logs\\%s\\bellmanFord\\log.txt\n", horario);
	printf("Log gerado em: logs\\%s\\floyd_warshall\\log.txt\n", horario);
	system("pause");
}