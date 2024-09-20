#include <stdio.h>
#include "./modules/functions.c"

int main()
{
    do
    {
        printf("Digite o numero de pontos: ");
        scanf("%d", &numPontos);
        while (getchar() != '\n')
            ;

        if (numPontos > 0)
        {
            break;
        }
        else
        {
            printf("Digite um valor valido!\n");
        }
    } while (1);

    initPontos();
    initMatrizDeRotas();
    menu();

    freePontos();
    freeMatrizDeRotas();

    return 0;
}
