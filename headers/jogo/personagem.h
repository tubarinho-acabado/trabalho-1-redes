#ifndef __personagem__
#define __personagem__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define DIRE_ERRO  0
#define DIRE_CIMA  1
#define DIRE_BAIXO 2
#define DIRE_ESQ   3
#define DIRE_DIR   4

typedef struct {
    ALLEGRO_BITMAP *desenho;
    unsigned char x, y;
} Personagem;

Personagem *cria_personagem(unsigned char x, unsigned char y);
void desaloca_personagem(Personagem *p);
void muda_posicao(Personagem *p, unsigned char lin, unsigned char col);
void move_personagem(Personagem *p, unsigned char direcao);

#endif