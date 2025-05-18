#include <stdlib.h>
#include <stdio.h>
#include "../../headers/graficos/imagens.h"
#include "../../headers/graficos/desenha.h"
#include "../../headers/jogo/fim.h"

Fim *cria_fim() {
    Fim *fim;

    fim = malloc (sizeof (Fim));
    if (!fim) {
        printf ("Vishe, nao deu pra alocar :(\n");
        return NULL;
    }

    fim->sair = cria_botao (IMG_BOTAO_SAIR, ALTURA_BOTAO_SAIR);
    fim->fundo = al_load_bitmap(IMG_FIM);

    return fim;
}

void destroi_fim(Fim *fim) {
    destroi_botao(fim->sair);
    al_destroy_bitmap(fim->fundo);
    free(fim);
}

int mostra_fim(Interface *inter, Fim *fim) {
    int retorno;

    if (inter->fechou)
    return SAIR;

    retorno = FIM;

    ALLEGRO_EVENT evento;
    inicia_tempo(inter);
    al_wait_for_event (inter->fila, &evento);

    while (evento.type != ALLEGRO_EVENT_DISPLAY_CLOSE && retorno == FIM) {
        if (evento.type == ALLEGRO_EVENT_TIMER) {
            desenha_fundo(fim->fundo);
            desenha_botao(fim->sair);
            atualiza_botao (fim->sair);
            al_flip_display ();
        }

        if (botao_pressionado (fim->sair))
            retorno = SAIR;

        al_wait_for_event (inter->fila, &evento);
    }

    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        inter->fechou = 1;

    return retorno;
}
