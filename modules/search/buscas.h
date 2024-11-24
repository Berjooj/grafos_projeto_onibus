#ifndef BUSCAS_H
#define BUSCAS_H

void profundidade(int origem, int destino);
void _profundidade(int origem, int destino);

void largura(int origem, int destino);
void _largura(int origem, int destino);

void bellmanFord(int origem, int destino);
void _bellmanFord(int origem, int destino);

void dijkstra(int origem, int destino);
void _dijkstra(int origem, int destino);

void floyd_warshall(int origem, int destino);
void _floyd_warshall(int origem, int destino);

#endif
