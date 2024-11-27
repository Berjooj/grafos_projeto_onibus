#include <stdio.h>
#include <stdlib.h>

#include "./modules/functions.c"
#include "./modules/views/menu.c"

int main() {
	limparTela();

	char nomeArquivo[100];

	printf("Realizar o carregamento completo (1 - sim; 0 - nao) ? ");
	int tipoCarregamento = 0;

	scanf("%d", &tipoCarregamento);

	if (tipoCarregamento == 1)
		sprintf(nomeArquivo, "./config/data_completa.json");
	else
		sprintf(nomeArquivo, "./config/data.json");

	init(1, nomeArquivo);

	menu();

	system("pause");

	return 0;
}