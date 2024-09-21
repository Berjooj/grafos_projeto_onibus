#include <stdio.h>
#include <stdlib.h>

#include "./modules/functions.c"
#include "./modules/views/menu.c"

int main() {
	// do {
	// 	printf("Digite o numero de pontos: ");
	// 	scanf("%d", &MAX_SIZE);
	// 	while (getchar() != '\n');

	// 	if (MAX_SIZE > 0)
	// 		break;
	// 	else
	// 		printf("Digite um valor valido!\n");
	// } while (1);

	MAX_SIZE = 10;
	init(1);

	menu();

	system("pause");
	return 0;
}
