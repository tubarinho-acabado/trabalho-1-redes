#ifndef __mapa__
#define __mapa__

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define TAM_QUADRADO 80
#define SEM_TESOURO 0
#define TESOURO_ENTERRADO 1
#define TESOURO_ACHADO 2

typedef struct {
    ALLEGRO_BITMAP *desenho;
    ALLEGRO_BITMAP *x, *tesouro;
    ALLEGRO_BITMAP *esteve_aqui;
    ALLEGRO_BITMAP *grade;
    bool **m_esteve_aqui;
    unsigned char **m_tesouros;
} Mapa;

Mapa *cria_mapa();
void destroi_mapa(Mapa *m);
void insere_tesouro(Mapa *m, bool enterrado, unsigned char lin, unsigned char col);
void marca_presenca(Mapa *m, unsigned char lin, unsigned char col);
bool passou_aqui(Mapa *m, unsigned char lin, unsigned char col);
bool tem_tesouro_enterrado(Mapa *m, unsigned char lin, unsigned char col);
bool tem_tesouro_achado(Mapa *m, unsigned char lin, unsigned char col);
bool mapa_limpo(Mapa *m);

#endif