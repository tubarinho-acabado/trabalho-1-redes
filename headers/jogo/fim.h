#ifndef __fim__
#define __fim__

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "botao.h"
#include "interface.h"

#define ALTURA_BOTAO_SAIR 220

typedef struct {
  ALLEGRO_BITMAP *fundo;
  Botao *sair;
} Fim;

Fim *cria_fim();

void destroi_fim(Fim *fim);

int mostra_fim(Interface *inter, Fim *fim);

#endif