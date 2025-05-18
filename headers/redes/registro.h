#ifndef __registro__
#define __registro__

#include "mensagem.h"

typedef struct {
    Mensagem *ult_enviada;
    Mensagem *atual;
    Mensagem *ult_recebida;
} Registro;



#endif