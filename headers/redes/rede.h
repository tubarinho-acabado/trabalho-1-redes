#ifndef __rede__
#define __rede__

#include <stdbool.h>
#include "mensagem.h"
#include "../jogo/mapa.h"
#include "../jogo/personagem.h"

#define MSG_ACK 0
#define MSG_NACK 1
#define MSG_OK_ACK 2
#define MSG_POS_INICIAL 3
#define MSG_TAMANHO 4
#define MSG_DADOS 5
#define MSG_TEXTO_ACK_NOME 6
#define MSG_VIDEO_ACK_NOME 7
#define MSG_IMAGEM_ACK_NOME 8
#define MSG_FIM_ARQUIVO 9
#define MSG_DIREITA 10
#define MSG_CIMA 11
#define MSG_BAIXO 12
#define MSG_ESQUERDA 13
#define MSG_JOGO_ACABOU 14
#define ERRO 15

typedef struct {
    unsigned char seq_envia, seq_recebe;
    int soquete;
} Rede;

Rede *cria_rede();
void destroi_rede(Rede *r);

// Cliente manda uma mensagem avisando para o servidor onde quer ir
// Retorna a mensagem de resposta do servidor
Mensagem *avisa_direcao(Rede *r, unsigned char direcao);

Mensagem *avisa_pos_inicial(Rede *r, unsigned char x, unsigned char y);

// Servidor recebe uma direcao do cliente e atualiza o jogo
void recebe_direcao(Rede *r, Mapa *mapa, Personagem *p);

void recebe_pos_inicial(Rede *r, Personagem *per);

#endif