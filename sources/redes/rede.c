#include <stdlib.h>
#include <stdio.h>
#include "../../headers/jogo/jogo.h"
#include "../../headers/redes/rede.h"
#include "../../headers/redes/conexao.h"

Rede *cria_rede() {
    Rede *r = (Rede *) malloc(sizeof(Rede));
    if(r == NULL) return NULL;
    r->seq_envia = 0;
    r->seq_recebe = 0;
    r->soquete = cria_raw_socket();
    return r;
}

void destroi_rede(Rede *r) {
    if(r == NULL)
        return;
    destroi_raw_socket(r->soquete);
    free(r);
}

void pos_inicial(Mensagem *msg, int *x, int *y) {
    *x = msg->dados[0];
    *y = msg->dados[1];
}

void atualiza_sequencia_envia(Rede *r) {
    r->seq_envia++;
    r->seq_envia = r->seq_envia % 32;
}

void atualiza_sequencia_recebe(Rede *r) {
    r->seq_recebe++;
    r->seq_recebe = r->seq_recebe % 32;
}

unsigned char tipo_direcao(unsigned char direcao) {
    unsigned char tipo;
    switch (direcao) {
    case DIRE_CIMA:
        tipo = MSG_CIMA;
        break;
    case DIRE_BAIXO:
        tipo = MSG_BAIXO;
        break;
    case DIRE_DIR:
        tipo = MSG_DIREITA;
        break;
    case DIRE_ESQ:
        tipo = MSG_ESQUERDA;
        break;
    default:
        break;
    }
    return tipo;
}

bool ack(unsigned char tipo) {
    if(tipo == MSG_ACK || tipo == MSG_OK_ACK ||
       tipo == MSG_TEXTO_ACK_NOME || tipo == MSG_IMAGEM_ACK_NOME ||
       tipo == MSG_VIDEO_ACK_NOME)
            return true;
    return false;
}

int confere_mensagem_recebida(Rede *r, Mensagem *msg) {
    if(msg == NULL)
        return 1;

    printf("seq: %d, seq rec: %d\n", msg->seq, r->seq_recebe);
    if(msg->seq != r->seq_recebe) {
        destroi_mensagem(msg);
        return 1;
    }

    atualiza_sequencia_recebe(r);
    return 0;
}

Mensagem *envia_mensagem_2bytes(Rede *r, unsigned char tipo, unsigned char byte1, unsigned char byte2) {
    unsigned char *dados = (unsigned char *) malloc(sizeof(unsigned char) * 2);
    if(dados == NULL) return NULL;

    dados[0] = byte1;
    dados[1] = byte2;

    Mensagem *msg = cria_mensagem(2, r->seq_envia, tipo, 0, dados);
    if(msg == NULL) return NULL;

    Mensagem *resposta = NULL;
    int result;
    int conf;
    do {
        destroi_mensagem(resposta);
        int pr = envia_mensagem(msg, r->soquete);
        result = recebe_mensagem(r->soquete, &resposta);
        conf = confere_mensagem_recebida(r, resposta);
        printf("result %d, conf mens %d, env %d\n", result, conf, pr);

    } while(result != 0 || conf || !ack(resposta->tipo));

    printf("ackerss\n");

    destroi_mensagem(msg);
    atualiza_sequencia_recebe(r);
    atualiza_sequencia_envia(r);
    return resposta;
}

Mensagem *avisa_direcao(Rede *r, unsigned char direcao) {
    return envia_mensagem_2bytes(r, tipo_direcao(direcao), 0, 0);
}

Mensagem *avisa_pos_inicial(Rede *r, unsigned char x, unsigned char y) {
    return envia_mensagem_2bytes(r, MSG_POS_INICIAL, x, y);
}

bool achou_tesouro(Mensagem *msg, char **tipo_arq) {
    bool tem_tesouro = false;
    *tipo_arq = NULL;

    switch (msg->tipo) {
    case MSG_TEXTO_ACK_NOME:
        tem_tesouro = true;
        *tipo_arq = ".txt";
        break;
    case MSG_VIDEO_ACK_NOME:
        tem_tesouro = true;
        *tipo_arq = ".mp4";
        break;
    case MSG_IMAGEM_ACK_NOME:
        tem_tesouro = true;
        *tipo_arq = ".jpg";
        break;
    default:
        break;
    }
    return tem_tesouro;
}

void atualiza_posicao_jogador(Personagem *per, Mensagem *msg) {
    switch (msg->tipo) {
    case MSG_CIMA:
        move_personagem(per, DIRE_CIMA);
        break;
    case MSG_BAIXO:
        move_personagem(per, DIRE_BAIXO);
        break;
    case MSG_ESQUERDA:
        move_personagem(per, DIRE_ESQ);
        break;
    case MSG_DIREITA:
        move_personagem(per, DIRE_DIR);
        break;
    default:
        break;
    }
}

void recebe_direcao(Rede *r, Mapa *mapa, Personagem *per) {
    Mensagem *msg;
    int result = recebe_mensagem(r->soquete, &msg);
    if(result == 1)
        return;

    unsigned char tipo;
    if(result == -1 || confere_mensagem_recebida(r, msg)) {
        tipo = MSG_NACK;
    }
    else {
        atualiza_posicao_jogador(per, msg);
        marca_presenca(mapa, per->x, per->y);
        tipo = MSG_OK_ACK;
        if(tem_tesouro_enterrado(mapa, per->x, per->y))
            tipo = MSG_TEXTO_ACK_NOME;
    }

    Mensagem *enviar = cria_mensagem(0, r->seq_envia, tipo, 0, NULL);
    envia_mensagem(enviar, r->soquete);
    atualiza_sequencia_envia(r);
    //envia_mensagem_2bytes(r, tipo, 0, 0);
    destroi_mensagem(msg);
    destroi_mensagem(enviar);
}

void recebe_pos_inicial(Rede *r, Personagem *per) {
    Mensagem *msg;
    int result = recebe_mensagem(r->soquete, &msg);
    if(result == 1)
        return;

    unsigned char tipo;
    if(result == -1 || confere_mensagem_recebida(r, msg)) {
        tipo = MSG_NACK;
    }
    else {
        muda_posicao(per, msg->dados[0], msg->dados[1]);
        //arrumar
        tipo = MSG_ACK;
    }

    Mensagem *enviar = cria_mensagem(4, r->seq_envia, tipo, 0, "DADO");
    envia_mensagem(enviar, r->soquete);
    //envia_mensagem_2bytes(r, tipo, 255, 255);
    atualiza_sequencia_envia(r);
    destroi_mensagem(msg);
    destroi_mensagem(enviar);
}