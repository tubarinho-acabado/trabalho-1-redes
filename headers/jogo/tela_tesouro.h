#ifndef __tela_tesouro__
#define __tela_tesouro__

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "botao.h"
#include "interface.h"

#define ALTURA_BOTOES_TESOURO 500

typedef struct {
  ALLEGRO_BITMAP *fundo;
  Botao *desenterrar;
  Botao *continuar;
  bool enviando_tesouro;
} Tela_tesouro;

Tela_tesouro *cria_tela_tesouro();

void destroi_tela_tesouro (Tela_tesouro *tes);

int mostra_tela_tesouro (Interface *inter, Tela_tesouro *tes, Mapa *mapa, Personagem *per);

#endif