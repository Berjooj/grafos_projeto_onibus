#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct {
	char nome[100];
	int lotacaoMaxima;
	int lotacaoAtual;

	// Em litros
	float capacidadeCombustivel;

	// Km por litro de gasolina
	float autonomia;
} Onibus;

typedef struct
{
	char nome[100];
	double distancia;
	int tempoPercurso;
} Rota;

typedef struct
{
	char endereco[100];
	bool eGaragem;
	double lat;
	double lng;
} Ponto;

typedef struct
{
	char nome[100];
	int **rotas;
} Percurso;

int MAX_SIZE;
Onibus *frota;
Ponto *pontos;
Rota *rotas;
Percurso *percursos;

#endif