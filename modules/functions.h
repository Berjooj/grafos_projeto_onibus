#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void initPontos();
void preenchePontos();
void pontosPreenchidos();
void initMatrizDeRotas();
void listarRotas();
void cadastrarRotas();
void inserirRota(int origem, int destino, double distancia, int tempoPercurso);
void listarMatriz();
void listarPontos();
void freePontos();
void freeMatrizDeRotas();
void menu();

#endif
