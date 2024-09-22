#include <stdio.h>
#include <stdlib.h>

#include "./modules/functions.c"
#include "./modules/views/menu.c"

int main() {
	limparTela();

	init(1);

	menu();

	system("pause");
	return 0;
}
