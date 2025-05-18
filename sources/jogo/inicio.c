#include <stdlib.h>
#include <stdio.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/graficos/desenha.h"
#include "../../headers/jogo/inicio.h"
#include "../../headers/jogo/jogo.h"

Inicio *cria_inicio () {
  Inicio *ini;

  ini = malloc (sizeof (Inicio));
  if (!ini) {
    printf ("Vishe, nao deu pra alocar :(\n");
    return NULL;
  }

  ini->jogar = cria_botao (IMG_BOTAO_JOGAR, ALTURA_BOTAO_JOGAR);
  ini->fundo = al_load_bitmap(IMG_INICIO);

  return ini;
}

int mostra_inicio (Interface *inter, Inicio *ini, Mapa *mapa, Personagem *per) {
  int retorno;

  if (inter->fechou)
    return SAIR;

  retorno = INICIO;

  ALLEGRO_EVENT evento;
  inicia_tempo(inter);
  al_wait_for_event (inter->fila, &evento);

  while (evento.type != ALLEGRO_EVENT_DISPLAY_CLOSE && retorno == INICIO) {
    if (evento.type == ALLEGRO_EVENT_TIMER) {
      desenha_fundo(ini->fundo);
      desenha_botao(ini->jogar);
      atualiza_botao (ini->jogar);
      al_flip_display ();
    }

    if (botao_pressionado (ini->jogar))
      retorno = JOGO;

    al_wait_for_event (inter->fila, &evento);
  }

  if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    inter->fechou = 1;

  return retorno;
}

void destroi_inicio (Inicio *ini) {
  destroi_botao (ini->jogar);
  al_destroy_bitmap (ini->fundo);
  free (ini);
}