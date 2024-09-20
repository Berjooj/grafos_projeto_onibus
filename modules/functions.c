#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"
#include "types.h"

Ponto *pontos;
Rota **matrizDeRotas;
int numPontos;
void initPontos()
{
    pontos = (Ponto *)malloc(numPontos * sizeof(Ponto));
}

void initMatrizDeRotas()
{
    matrizDeRotas = (Rota **)malloc(numPontos * sizeof(Rota *));
    for (int i = 0; i < numPontos; i++)
    {
        matrizDeRotas[i] = (Rota *)malloc(numPontos * sizeof(Rota));
        for (int j = 0; j < numPontos; j++)
        {
            matrizDeRotas[i][j].existe = false;
        }
    }
}

void preenchePontos()
{
    for (int i = 0; i < numPontos; i++)
    {
        printf("\nPonto %d:\n", i + 1);

        printf("Digite o endereco do ponto: ");
        fgets(pontos[i].endereco, sizeof(pontos[i].endereco), stdin);
        pontos[i].endereco[strcspn(pontos[i].endereco, "\n")] = '\0';

        int eGaragem;
        printf("Este ponto e uma garagem? (1 para Sim, 0 para Nao): ");
        while (scanf("%d", &eGaragem) != 1 || (eGaragem != 0 && eGaragem != 1))
        {
            printf("Entrada invalida. Digite 1 para Sim ou 0 para Nao: ");
            while (getchar() != '\n')
                ;
        }
        pontos[i].eGaragem = (eGaragem == 1);

        printf("Digite a latitude do ponto: ");
        while (scanf("%lf", &pontos[i].lat) != 1)
        {
            printf("Entrada invalida. Digite a latitude do ponto: ");
            while (getchar() != '\n')
                ;
        }
        printf("Digite a longitude do ponto: ");
        while (scanf("%lf", &pontos[i].lgn) != 1)
        {
            printf("Entrada invalida. Digite a longitude do ponto: ");
            while (getchar() != '\n')
                ;
        }

        while (getchar() != '\n')
            ;
    }
}

// Apenas para pré-preencher de maneira rápida, nunca utilizar preenchePontos() e pontosPreenchidos() na mesma execução
void pontosPreenchidos()
{
    for (int i = 0; i < numPontos; i++)
    {
        snprintf(pontos[i].endereco, sizeof(pontos[i].endereco), "%d", i + 1);
        pontos[i].eGaragem = false;
        pontos[i].lat = 12.1;
        pontos[i].lgn = 19.2;
    }
}

void cadastrarRotas()
{
    int origem, destino, tempoPercurso;
    double distancia;
    char opcao;

    printf("\nCadastro de Rotas:\n");

    do
    {
        printf("Digite o ponto de origem (1 a %d): ", numPontos);
        while (scanf("%d", &origem) != 1 || origem < 1 || origem > numPontos)
        {
            printf("Entrada invalida. Digite um ponto de origem valido (1 a %d): ", numPontos);
            while (getchar() != '\n')
                ;
        }
        origem--;
        printf("Digite o ponto de destino (1 a %d): ", numPontos);
        while (scanf("%d", &destino) != 1 || destino < 1 || destino > numPontos || destino == origem + 1)
        {
            printf("Entrada invalida. Digite um ponto de destino valido (1 a %d), diferente da origem: ", numPontos);
            while (getchar() != '\n')
                ;
        }
        destino--;
        printf("Digite a distancia da rota em km: ");
        while (scanf("%lf", &distancia) != 1 || distancia <= 0)
        {
            printf("Entrada invalida. Digite uma distância valida em km: ");
            while (getchar() != '\n')
                ;
        }

        printf("Digite o tempo de percurso em minutos: ");
        while (scanf("%d", &tempoPercurso) != 1 || tempoPercurso <= 0)
        {
            printf("Entrada invalida. Digite um tempo de percurso valido em minutos: ");
            while (getchar() != '\n')
                ;
        }

        while (getchar() != '\n')
            ;

        inserirRota(origem, destino, distancia, tempoPercurso);

        printf("\nDeseja inserir outra rota? (s/n): ");
        opcao = getchar();
        while (getchar() != '\n')
            ;

    } while (opcao == 's' || opcao == 'S');
}

void inserirRota(int origem, int destino, double distancia, int tempoPercurso)
{
    if (origem >= 0 && origem < numPontos && destino >= 0 && destino < numPontos)
    {
        snprintf(matrizDeRotas[origem][destino].nome, sizeof(matrizDeRotas[origem][destino].nome), "%s - %s", pontos[origem].endereco, pontos[destino].endereco);
        matrizDeRotas[origem][destino].distancia = distancia;
        matrizDeRotas[origem][destino].tempoPercurso = tempoPercurso;
        matrizDeRotas[origem][destino].existe = true;
    }
    else
    {
        printf("Erro na Insercao.\n");
    }
}

void listarMatriz()
{
    printf("\nMatriz de Adjacencia das Rotas:\n");
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (matrizDeRotas[i][j].existe)
            {
                // printf("[Nome: %s, Dist: %.1f km, Tempo: %d min] ", matrizDeRotas[i][j].nome, matrizDeRotas[i][j].distancia, matrizDeRotas[i][j].tempoPercurso);
                printf("[-] ");
            }
            else
            {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
}

void listarPontos()
{
    printf("\nPontos:\n");
    for (int i = 0; i < numPontos; i++)
    {
        printf("Endereco: %s\nlatitude: %.2f\nlongitude: %.2f\nGaragem: %d\n\n", pontos[i].endereco, pontos[i].lat, pontos[i].lgn, pontos[i].eGaragem);
    }
}

void listarRotas()
{
    printf("Rotas:\n");
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (matrizDeRotas[i][j].existe)
            {
                printf("Nome Rota: %s\nDistancia: %.2fkm\nTempo de Percurso: %dminutos\n\n", matrizDeRotas[i][j].nome, matrizDeRotas[i][j].distancia, matrizDeRotas[i][j].tempoPercurso);
            }
        }
    }
}
void menu()
{
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1. Cadastrar Pontos\n");
        printf("2. Cadastrar Rotas\n");
        printf("3. Listar Pontos\n");
        printf("4. Listar Rotas\n");
        printf("5. Listar Matriz de Rotas\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        while (getchar() != '\n')
            ;

        switch (opcao)
        {
        case 1:
            // preenchePontos();
            pontosPreenchidos();
            break;
        case 2:
            cadastrarRotas();
            break;
        case 3:
            listarPontos();
            break;
        case 4:
            listarRotas();
            break;
        case 5:
            listarMatriz();
            break;
        case 6:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    } while (opcao != 6);
}

void freePontos()
{
    free(pontos);
}

void freeMatrizDeRotas()
{
    for (int i = 0; i < numPontos; i++)
    {
        free(matrizDeRotas[i]);
    }
    free(matrizDeRotas);
}
