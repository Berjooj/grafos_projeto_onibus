#include <stdbool.h>
#ifndef TYPES_H
#define TYPES_H

typedef struct
{
    char nome[100];
    double distancia;
    int tempoPercurso;
    bool existe;
} Rota;

typedef struct
{
    char endereco[100];
    bool eGaragem;
    double lat;
    double lgn;
} Ponto;

#endif