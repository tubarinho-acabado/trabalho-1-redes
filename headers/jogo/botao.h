#ifndef __botao__
#define __botao__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include "interface.h"

typedef struct {
  ALLEGRO_BITMAP *desenho;
  bool pressionado;
  bool foi_pressionado;
  short x;     //coordenada x do canto inferior esquerdo
  short y;     //coordenada y do canto inferior esquerdo
} Botao;

//cria um botao
Botao *cria_botao (char *img_botao, int alt_pos);

//destroi um botao
void destroi_botao (Botao *bot);

bool atualiza_botao (Botao *bot);

bool botao_pressionado (Botao *bot);

#endif