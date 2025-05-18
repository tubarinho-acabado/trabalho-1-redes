#include "../../headers/graficos/desenha.h"

void desenha_no_quadrado(ALLEGRO_BITMAP *img, unsigned char lin, unsigned char col) {
    al_draw_bitmap(img,(float) TAM_QUADRADO*(lin), (float) TAM_QUADRADO*(7-col), 0);
}

void desenha_mapa(Mapa *m, bool serv) {
    if(m == NULL)
        return;

    al_draw_bitmap(m->desenho, 0, 0, 0);
    for(unsigned char i = 0; i < 8; i++)
        for(unsigned char j = 0; j < 8; j++) {
            if(m->m_esteve_aqui[i][j]) 
                desenha_no_quadrado(m->esteve_aqui, i, j);
            if(m->m_tesouros[i][j] == TESOURO_ACHADO)
                desenha_no_quadrado(m->tesouro, i, j);
            else if(m->m_tesouros[i][j] == TESOURO_ENTERRADO && serv)
                desenha_no_quadrado(m->x, i, j);
        }
    al_draw_bitmap(m->grade, 0, 0, 0);
}

void desenha_personagem(Personagem *p) {
    al_draw_bitmap(p->desenho, (float) TAM_QUADRADO*(p->x), (float) TAM_QUADRADO*(7-p->y), 0);
}

void desenha_botao (Botao *bot) {
  short larg, alt;

  larg = al_get_bitmap_width (bot->desenho);
  alt = al_get_bitmap_height (bot->desenho);

  al_draw_scaled_bitmap (bot->desenho, 0, 0, larg, alt, bot->x, bot->y, larg, alt, 0);
}

void desenha_fundo(ALLEGRO_BITMAP *fundo) {
    al_draw_bitmap(fundo, 0, 0, 0);
}