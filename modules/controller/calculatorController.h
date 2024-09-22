
#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H
#include "../types.h"

void calculaQuantidadeOnibusParada(int indiceParada);
void calculaQuantidadeOnibusRota(int rota);
int rotasPorOnibus(Percurso percurso);
int paradasPorOnibus(Percurso percurso);
int arestasPorOnibus(Percurso percurso);

#endif