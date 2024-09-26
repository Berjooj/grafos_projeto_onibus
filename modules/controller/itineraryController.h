#include "../types.h"

#ifndef ITINERARYCONTROLLER_H
#define ITINERARYCONTROLLER_H

void adicionarPontoRota(Percurso *percursoTemp);
void removerPontoRota(Percurso *percursoTemp);
void exibirPontoRota(Percurso *percursoTemp);
void exibirMatrizPontoRota(Percurso *percursoTemp);
void salvarPontoRota(Percurso *percursoTemp, int indiceOnibus);
void copiarRoteiro(Percurso *percursoTemp, int idOnibus);
void limparRoteiro(Percurso *percursoTemp);
int calcularGrauEntrada(Percurso *percursoTemp, int indice);
int calcularGrauSaida(Percurso *percursoTemp, int indice);
void consultarPonto(Percurso *percursoTemp);
void consultarAresta(Percurso *percursoTemp);

#endif