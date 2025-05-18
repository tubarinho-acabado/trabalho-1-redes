#include <stdlib.h>
#include <stdio.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/jogo/mapa.h"
#include "../../headers/jogo/personagem.h"

Personagem *cria_personagem(unsigned char x, unsigned char y) {
    Personagem *p = (Personagem *) malloc(sizeof(Personagem));
    if(p == NULL)
        return NULL;

    p->desenho = al_load_bitmap(IMG_PERSONAGEM);
    if(p->desenho == NULL)
        return NULL;

    p->x = x;
    p->y = y;
    return p;
}

void desaloca_personagem(Personagem *p) {
    if(p == NULL)
        return;

    al_destroy_bitmap(p->desenho);
    free(p);
}

/*void desenha_personagem(Personagem *p) {
    al_draw_bitmap(p->desenho, (float) TAM_QUADRADO*(7-p->x), (float) TAM_QUADRADO*(7-p->y), 0);
}*/

void muda_posicao(Personagem *p, unsigned char lin, unsigned char col) {
    if(p == NULL || lin >= 8 || col >= 8)
        return;
    p->x = lin;
    p->y = col;
}

void move_personagem(Personagem *p, unsigned char direcao) {
    if(p == NULL)
        return;
    switch (direcao) {
    case DIRE_CIMA:
        if(p->y < 7)
            p->y++;
        break;
    case DIRE_BAIXO:
        if(p->y)
            p->y--;
        break;
    case DIRE_DIR:
        if(p->x < 7)
            p->x++;
        break;
    case DIRE_ESQ:
        if(p->x)
            p->x--;
    default:
        break;
    }
}