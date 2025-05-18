#include <stdlib.h>
#include <stdio.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/graficos/desenha.h"
#include "../../headers/jogo/tela_tesouro.h"

Tela_tesouro *cria_tela_tesouro () {
    Tela_tesouro *tes;

    tes = malloc (sizeof (Tela_tesouro));
    if (!tes) {
        printf ("Vishe, nao deu pra alocar :(\n");
        return NULL;
    }

    tes->desenterrar = cria_botao (IMG_BOTAO_DESENTERRAR, ALTURA_BOTOES_TESOURO);
    tes->continuar = cria_botao (IMG_BOTAO_SAIR, ALTURA_BOTOES_TESOURO);
    tes->fundo = al_load_bitmap(IMG_TELA_TESOURO);
    tes->enviando_tesouro = 0;

    return tes;
}

void destroi_tela_tesouro (Tela_tesouro *tes) {
    destroi_botao (tes->desenterrar);
    destroi_botao (tes->continuar);
    al_destroy_bitmap (tes->fundo);
    free (tes);
}

int mostra_tela_tesouro (Interface *inter, Tela_tesouro *tes, Mapa *mapa, Personagem *per) {
    int retorno;

    if (inter->fechou)
        return SAIR;

    retorno = TESOURO_TELA;

    ALLEGRO_EVENT evento;
    inicia_tempo(inter);
    al_wait_for_event (inter->fila, &evento);

    while (evento.type != ALLEGRO_EVENT_DISPLAY_CLOSE && retorno == TESOURO_TELA) {
        if (evento.type == ALLEGRO_EVENT_TIMER) {
            desenha_mapa(mapa, 0);
            desenha_personagem(per);
            desenha_fundo(tes->fundo);

            if(!tes->enviando_tesouro) {
                desenha_botao(tes->desenterrar);
                atualiza_botao (tes->desenterrar);
            }
            else {
                desenha_botao(tes->continuar);
                atualiza_botao (tes->continuar);
            }

            al_flip_display ();
        }

        if(botao_pressionado(tes->desenterrar) && !tes->enviando_tesouro)
            tes->enviando_tesouro = 1;

        if(botao_pressionado(tes->continuar) && tes->enviando_tesouro) {
            tes->enviando_tesouro = 0;
            retorno = JOGO;
        }

        al_wait_for_event (inter->fila, &evento);
    }

    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        inter->fechou = 1;

    return retorno;
}