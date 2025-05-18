#ifndef __jogo__
#define __jogo__

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "mapa.h"
#include "personagem.h"
#include "interface.h"
#include "../redes/rede.h"

typedef struct {
    Mapa *mapa;
    Personagem *per;
    bool pode_andar;
} Jogo;

Jogo *cria_jogo();

void destroi_jogo(Jogo *jog);

int mostra_jogo(Interface *inter, Jogo *jog, Rede *r, bool serv);

#endif