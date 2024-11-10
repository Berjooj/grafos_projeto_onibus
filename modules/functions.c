#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./file/reader.c"
#include "./file/exporter.c"
#include "./views/list.c"
#include "types.h"

void init(int lerArquivo) {

	const char *nome_arquivo = "./config/data.json";
	const char *nome_arquivo_exportacao = "./output/resultado_grafo.json";
	char *json_string = carregar_arquivo_json(nome_arquivo);

	if (json_string) {
	Grafo *grafo = parse_json_para_grafo(json_string);
	exibirLista(grafo);
	exportar_grafo(grafo, nome_arquivo_exportacao);

	free(json_string);
	liberar_grafo(grafo);
	}
}

void limparTela() {

	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
		return;
}