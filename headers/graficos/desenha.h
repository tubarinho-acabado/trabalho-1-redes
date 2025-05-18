#ifndef __desenha__
#define __desenha__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "../jogo/mapa.h"
#include "../jogo/personagem.h"
#include "../jogo/botao.h"
#include "../jogo/interface.h"

void desenha_mapa(Mapa *m, bool serv);
void desenha_personagem(Personagem *p);
void desenha_botao(Botao *bot);
void desenha_fundo(ALLEGRO_BITMAP *fundo);

#endif