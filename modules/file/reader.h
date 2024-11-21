#include <stdbool.h>

#include "../../dependencies/cJSON/cJSON.h"
#include "../types.h"

#ifndef READER_H
#define READER_H

char *carregar_arquivo_json(const char *filename);
Grafo *parse_json_para_grafo(const char *json_string);

#endif
