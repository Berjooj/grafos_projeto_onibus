#include "../types.h"

#ifndef ITINERARYCONTROLLER_H
#define ITINERARYCONTROLLER_H

void adicionarPontoRota(Percurso *percursoTemp);
void removerPontoRota(Percurso *percursoTemp);
void exibirPontoRota(Percurso *percursoTemp);
void exibirMatrizPontoRota(Percurso *percursoTemp);
void salvarPontoRota(Percurso *percursoTemp,int indiceOnibus);

#endif