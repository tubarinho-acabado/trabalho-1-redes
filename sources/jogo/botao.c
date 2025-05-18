#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/jogo/botao.h"

short calcula_meio (short larg_botao) {
  return (TELA - larg_botao) / 2;
}

//cria um botao
Botao *cria_botao (char *img_botao, int alt_pos) {
  Botao *bot;

  bot = malloc (sizeof (Botao));
  if (!bot) {
    printf ("Vishe, nao deu pra alocar :(\n");
    return NULL;
  }

  bot->desenho = al_load_bitmap (img_botao);
  bot->foi_pressionado = 0;
  bot->pressionado = 0;
  bot->x = calcula_meio (al_get_bitmap_width(bot->desenho));
  bot->y = alt_pos;

  return bot;
}

//destroi um botao
void destroi_botao (Botao *bot) {
  al_destroy_bitmap (bot->desenho);
  free (bot);
}

bool verifica_posicao (Botao *bot, ALLEGRO_MOUSE_STATE *mouse) {
  if ((mouse->x >= bot->x && mouse->x < bot->x + al_get_bitmap_width(bot->desenho)) &&
      (mouse->y < bot->y + al_get_bitmap_height(bot->desenho) && mouse->y >= bot->y))
      return 1;
  return 0;
}

bool atualiza_botao (Botao *bot) {
  ALLEGRO_MOUSE_STATE mouse;
  bool no_botao;
  short x, y;

  al_get_mouse_state(&mouse);
  no_botao = verifica_posicao (bot, &mouse);

  if ((mouse.buttons & 1) && no_botao) {
    bot->foi_pressionado = 1;
    bot->pressionado = 1;
  }
  else
    bot->pressionado = 0;

  return no_botao;
}

bool botao_pressionado (Botao *bot) {
  if (bot->foi_pressionado && !bot->pressionado) {
    bot->foi_pressionado = 0;
    return 1;
  }
  return 0;
}