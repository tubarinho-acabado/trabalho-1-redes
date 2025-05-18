#include <stdlib.h>
#include <stdio.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/jogo/mapa.h"

Mapa *cria_mapa() {
    Mapa *m = (Mapa *) malloc(sizeof(Mapa));
    if(m == NULL)
        return NULL;

    m->desenho = al_load_bitmap(IMG_MAPA);
    m->esteve_aqui = al_load_bitmap(IMG_ESTEVE_AQUI);
    m->tesouro = al_load_bitmap(IMG_TESOURO_ACHADO);
    m->grade = al_load_bitmap(IMG_GRADE);
    m->x = al_load_bitmap(IMG_TESOURO_ENTERRADO);

    if(m->tesouro == NULL || m->desenho == NULL || m->grade == NULL || m->esteve_aqui == NULL || m->x == NULL)
        return NULL;

    m->m_esteve_aqui = (bool **) malloc(sizeof(bool *) * 8);
    m->m_tesouros = (unsigned char **) malloc(sizeof(unsigned char *) * 8);

    if(m->m_esteve_aqui == NULL || m->m_tesouros == NULL)
        return NULL;

    for(unsigned char i = 0; i < 8; i++) {
        m->m_esteve_aqui[i] = (bool *) malloc(sizeof(bool) * 8);
        m->m_tesouros[i] = (unsigned char *) malloc(sizeof(unsigned char) * 8);

        if(m->m_esteve_aqui[i] == NULL || m->m_tesouros[i] == NULL)
            return NULL;

        for(unsigned char j = 0; j < 8; j++) {
            m->m_esteve_aqui[i][j] = 0;
            m->m_tesouros[i][j] = 0;
        }
    }
     return m;   
}

void destroi_mapa(Mapa *m) {
    if(m == NULL)
        return;

    al_destroy_bitmap(m->desenho);
    al_destroy_bitmap(m->esteve_aqui);
    al_destroy_bitmap(m->tesouro);
    al_destroy_bitmap(m->grade);

    for(int i = 0; i < 8; i++) {
        free(m->m_esteve_aqui[i]);
        free(m->m_tesouros[i]);
    }

    free(m->m_esteve_aqui);
    free(m->m_tesouros);

    if(m->x != NULL)
        al_destroy_bitmap(m->x);

    free(m);
}

/*void desenha_no_quadrado(ALLEGRO_BITMAP *img, unsigned char lin, unsigned char col) {
    al_draw_bitmap(img,(float) TAM_QUADRADO*(7-lin), (float) TAM_QUADRADO*(7-col), 0);
}

void desenha_mapa(Mapa *m) {
    if(m == NULL)
        return;

    al_draw_bitmap(m->desenho, 0, 0, 0);
    for(unsigned char i = 0; i < 8; i++)
        for(unsigned char j = 0; j < 8; j++) {
            if(m->m_esteve_aqui[i][j]) 
                desenha_no_quadrado(m->esteve_aqui, i, j);
            if(m->m_tesouros[i][j] == TESOURO_ACHADO)
                desenha_no_quadrado(m->tesouro, i, j);
            else if(m->m_tesouros[i][j] == TESOURO_ENTERRADO)
                desenha_no_quadrado(m->x, i, j);
        }
    al_draw_bitmap(m->grade, 0, 0, 0); 
}*/

void marca_presenca(Mapa *m, unsigned char lin, unsigned char col) {
    if(m == NULL || lin >= 8 || col >= 8)
        return;

    m->m_esteve_aqui[lin][col] = true;
}

void insere_tesouro(Mapa *m, bool enterrado, unsigned char lin, unsigned char col) {
    if(m == NULL || lin >= 8 || col >= 8)
        return;

    if(enterrado)
        m->m_tesouros[lin][col] = TESOURO_ENTERRADO;
    else
        m->m_tesouros[lin][col] = TESOURO_ACHADO;
}

bool passou_aqui(Mapa *m, unsigned char lin, unsigned char col) {
    return lin < 8 && col < 8 && m->m_esteve_aqui[lin][col];
}

bool tem_tesouro_enterrado(Mapa *m, unsigned char lin, unsigned char col) {
    return lin < 8 && col < 8 && m->m_tesouros[lin][col] == TESOURO_ENTERRADO;
}

bool tem_tesouro_achado(Mapa *m, unsigned char lin, unsigned char col) {
    return lin < 8 && col < 8 && m->m_tesouros[lin][col] == TESOURO_ACHADO;
}

bool mapa_limpo(Mapa *m) {
    int cont = 0;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(m->m_tesouros[i][j] == TESOURO_ACHADO)
                cont++;
        }
    }

    return cont == 8;
}