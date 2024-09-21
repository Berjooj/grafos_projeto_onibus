#include "../../dependencies/cJSON/cJSON.h"

#ifndef READER_H
#define READER_H

void initArquivo();
void parseOnibus(cJSON *onibusArray);
void parseRotas(cJSON *rotasArray);
void parsePontos(cJSON *pontosArray);
void parsePercursos(cJSON *percursoArray);

#endif
