#include <stdlib.h>
#include "../../headers/redes/arquivo.h"

unsigned char *parte_do_arquivo(FILE *arq, unsigned char *tam) {
    unsigned char *dados = (unsigned char*) malloc(sizeof(unsigned char) * *tam);
    if(dados == NULL)
        return NULL;

    unsigned char result = fread(dados, sizeof(unsigned char), *tam, arq);

    if(result < *tam) {
        unsigned char *dados2 = (unsigned char *) realloc(dados, result);
        free(dados);
        dados = dados2;
        *tam = result;
    }
    return dados;
}