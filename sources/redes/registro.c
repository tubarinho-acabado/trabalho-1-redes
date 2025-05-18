#include <stdlib.h>
#include <stdio.h>
#include "../../headers/redes/registro.h"

Registro *cria_registro() {
    Registro *reg;

    reg = malloc (sizeof(Registro));
    if (reg == NULL) {
        printf("Algo deu errado na criacao do registro :(\n");
        return NULL;
    }

    reg->atual = NULL;
    reg->ult_enviada = NULL;
    reg->ult_recebida = NULL;

    return reg;
}

void destroi_registro(Registro *reg) {
    free(reg);
}

void atualiza_registro(Registro *reg) {

}