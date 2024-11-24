#include <stdio.h>
#include <stdlib.h>

#include "./modules/functions.c"
#include "./modules/views/menu.c"

int main() {
	// system("pause");

	limparTela();

	char nomeArquivo[100];

	sprintf(nomeArquivo, "./config/bkp_t10_b55_b56_linha_desconexa.json");
	// sprintf(nomeArquivo, "./config/data.json");

	init(1, nomeArquivo);

	menu();

	system("pause");

	return 0;
}