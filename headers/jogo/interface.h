#ifndef __interface__
#define __interface__

#include <allegro5/allegro5.h>
#include <stdbool.h>

#define TELA 640
#define FPS 24.0

#define INICIO 0
#define JOGO 1
#define TESOURO_TELA 2
#define FIM 3
#define SAIR 4

typedef struct {
  ALLEGRO_TIMER *cronometro;
  ALLEGRO_EVENT_QUEUE *fila;
  ALLEGRO_DISPLAY *tela;
  ALLEGRO_BITMAP *icone;
  bool fechou;
} Interface;

Interface *cria_interface ();

void mostra_icone (Interface *inter);

void inicia_tempo (Interface *inter);

void pausa_tempo(Interface *inter);

void retoma_tempo(Interface *inter);

void destroi_interface (Interface *inter);

#endif