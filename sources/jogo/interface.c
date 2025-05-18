#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/jogo/interface.h"

Interface *cria_interface () {
  Interface *inter;

  inter = malloc (sizeof (Interface));
  if (!inter) {
    printf ("Vishe, nao deu pra alocar :(\n");
    return NULL;
  }

  al_init ();
  al_init_image_addon ();
  al_init_primitives_addon ();
  al_install_keyboard ();
  al_install_mouse ();

  inter->cronometro = al_create_timer (1.0 / FPS);
  inter->fila = al_create_event_queue ();
  inter->tela = al_create_display (TELA, TELA);
  inter->icone = al_load_bitmap (IMG_PERSONAGEM);
  inter->fechou = 0;
  srand(time(NULL));

  if (inter->cronometro && inter->fila && inter->tela) {
    al_register_event_source (inter->fila, al_get_keyboard_event_source ());
    al_register_event_source (inter->fila, al_get_display_event_source (inter->tela));
    al_register_event_source (inter->fila, al_get_timer_event_source (inter->cronometro));
  }

  return inter;
}

void mostra_icone (Interface *inter) {
  al_set_display_icon (inter->tela, inter->icone);
}

void inicia_tempo (Interface *inter) {
  al_stop_timer (inter->cronometro);
  al_start_timer (inter->cronometro);
}

void pausa_tempo(Interface *inter) {
    al_stop_timer(inter->cronometro);
}

void retoma_tempo(Interface *inter) {
    al_resume_timer(inter->cronometro);
}

void destroi_interface (Interface *inter) {
  al_destroy_event_queue (inter->fila);
  al_destroy_display (inter->tela);
  al_destroy_bitmap (inter->icone);
  free (inter);
}