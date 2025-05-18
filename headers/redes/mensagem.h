#ifndef __mensagem__
#define __mensagem__

#include <stdbool.h>

#define MAX_DADOS 127
#define MIN_DADOS 10

typedef struct {
    unsigned char tam;
    unsigned char seq;
    unsigned char tipo;
    unsigned char checkSum;
    unsigned char *dados;
} Mensagem;

Mensagem *cria_mensagem(unsigned char tam, unsigned char seq, unsigned char tipo, unsigned char checkSum, unsigned char *dados);
int recebe_mensagem(int soquete, Mensagem **msg);
int envia_mensagem(Mensagem *msg, int soquete);
unsigned char calcula_checkSum(Mensagem *msg, unsigned char *buffer);
void destroi_mensagem(Mensagem *msg);

#endif