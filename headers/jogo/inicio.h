#ifndef __inicio__
#define __inicio__

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "botao.h"
#include "interface.h"
#include "mapa.h"
#include "personagem.h"

#define ALTURA_BOTAO_JOGAR 500

typedef struct {
  ALLEGRO_BITMAP *fundo;
  Botao *jogar;
} Inicio;

Inicio *cria_inicio ();

void destroi_inicio (Inicio *ini);

int mostra_inicio (Interface *inter, Inicio *ini, Mapa *mapa, Personagem *per);

//int mostra_inicio (Interface *inter, Inicio *ini);

#endif