#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

void exportarJson() {
	int i, j, k;
	FILE* arquivo = fopen("config/exported_data.json", "w");

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo para escrita!\n");
		return;
	}

	fprintf(arquivo, "{\n");

	// Exportar Onibus
	fprintf(arquivo, "\t\"onibus\": [\n");
	for (i = 0; i <= indices.indiceFrota; i++) {
		fprintf(arquivo, "\t\t{\n");
		fprintf(arquivo, "\t\t\t\"nome\": \"%s\",\n", frota[i].nome);
		fprintf(arquivo, "\t\t\t\"lotacaoMaxima\": %d,\n", frota[i].lotacaoMaxima);
		fprintf(arquivo, "\t\t\t\"lotacaoAtual\": %d,\n", frota[i].lotacaoAtual);
		fprintf(arquivo, "\t\t\t\"capacidadeCombustivel\": %.1f,\n", frota[i].capacidadeCombustivel);
		fprintf(arquivo, "\t\t\t\"autonomia\": %.1f\n", frota[i].autonomia);

		if (i == indices.indiceFrota) {
			fprintf(arquivo, "\t\t}\n");
		} else {
			fprintf(arquivo, "\t\t},\n");
		}
	}
	fprintf(arquivo, "\t],\n");

	// Exportar Rotas
	fprintf(arquivo, "\t\"rotas\": [\n");
	for (i = 0; i <= indices.indiceRota; i++) {
		fprintf(arquivo, "\t\t{\n");
		fprintf(arquivo, "\t\t\t\"nome\": \"%s\",\n", rotas[i].nome);
		fprintf(arquivo, "\t\t\t\"distancia\": %.1f,\n", rotas[i].distancia);
		fprintf(arquivo, "\t\t\t\"tempoPercurso\": %d\n", rotas[i].tempoPercurso);

		if (i == indices.indiceRota) {
			fprintf(arquivo, "\t\t}\n");
		} else {
			fprintf(arquivo, "\t\t},\n");
		}
	}
	fprintf(arquivo, "\t],\n");

	// Exportar Pontos
	fprintf(arquivo, "\t\"pontos\": [\n");
	for (i = 0; i <= indices.indicePonto; i++) {
		fprintf(arquivo, "\t\t{\n");
		fprintf(arquivo, "\t\t\t\"endereco\": \"%s\",\n", pontos[i].endereco);
		fprintf(arquivo, "\t\t\t\"eGaragem\": %s,\n", pontos[i].eGaragem ? "true" : "false");
		fprintf(arquivo, "\t\t\t\"lat\": %.5f,\n", pontos[i].lat);
		fprintf(arquivo, "\t\t\t\"lng\": %.5f\n", pontos[i].lng);

		if (i == indices.indicePonto) {
			fprintf(arquivo, "\t\t}\n");
		} else {
			fprintf(arquivo, "\t\t},\n");
		}
	}
	fprintf(arquivo, "\t],\n");

	// Exportar Percurso
	fprintf(arquivo, "\t\"percurso\": [\n");
	for (i = 0; i <= indices.indiceFrota; i++) {
		fprintf(arquivo, "\t\t{\n");
		fprintf(arquivo, "\t\t\t\"linha\": \"%s\",\n", frota[i].nome);
		fprintf(arquivo, "\t\t\t\"rotas\": [\n");

		for (j = 0; j <= indices.indicePonto; j++) {
			for (k = 0; k <= indices.indicePonto; k++) {
				if (percursos[i].rotas[j][k] == -1) {
					continue;
				}

				fprintf(arquivo, "\t\t\t\t{\n");
				fprintf(arquivo, "\t\t\t\t\t\"origem\": \"%s\",\n", pontos[j].endereco);
				fprintf(arquivo, "\t\t\t\t\t\"destino\": \"%s\",\n", pontos[k].endereco);
				fprintf(arquivo, "\t\t\t\t\t\"rota\": \"%s\"\n", rotas[percursos[i].rotas[j][k]].nome);

				if (j == indices.indicePonto) {
					fprintf(arquivo, "\t\t\t\t}\n");
				} else {
					fprintf(arquivo, "\t\t\t\t},\n");
				}
			}
		}

		fprintf(arquivo, "\t\t\t]\n");

		if (i == indices.indiceFrota) {
			fprintf(arquivo, "\t\t}\n");
		} else {
			fprintf(arquivo, "\t\t},\n");
		}
	}
	fprintf(arquivo, "\t]\n");

	fprintf(arquivo, "}\n");

	fclose(arquivo);
	printf("JSON exportado com sucesso para 'config/exported_data.json'!\n");
	system("pause");
}