#include <stdlib.h>
#include <stdio.h>
#include "../../headers/jogo/jogo.h"
#include "../../headers/graficos/desenha.h"

Jogo *cria_jogo() {
    Jogo *jog;

    jog = malloc(sizeof(Jogo));
    if (!jog) {
        printf ("Vishe, nao deu pra alocar o jogo :(\n");
        return NULL;
    }

    jog->mapa = cria_mapa();
    jog->per = cria_personagem(0, 0);
    jog->pode_andar = 1;

    return jog;
}

void destroi_jogo(Jogo *jog) {
    destroi_mapa(jog->mapa);
    desaloca_personagem(jog->per);
    free(jog);
}

void gera_coordenadas(unsigned char *x, unsigned char *y) {
    *x = rand() % 8;
    *y = rand() % 8;
}

void escolhe_posicoes(Rede *r, Mapa *mapa, Personagem *per) {
    unsigned char x, y;

    int cont = 0;
    while(cont < 9) {
        gera_coordenadas(&x, &y);
        if(cont == 8) {
            if(!tem_tesouro_enterrado(mapa, x, y)) {
                printf("x per %d y per %d\n", x, y);
                avisa_pos_inicial(r, x, y);
                muda_posicao(per, x, y);
                cont++;
            }
        }
        else {
            if(!tem_tesouro_enterrado(mapa, x, y)) {
                insere_tesouro(mapa, 1, x, y);
                cont++;
            }
        }
    }
}

void atualiza_posicao(Jogo *jog, Rede *r, ALLEGRO_EVENT evento) {
    if(evento.type == ALLEGRO_EVENT_KEY_DOWN /*&& jog->pode_andar*/) {
        marca_presenca(jog->mapa, jog->per->x, jog->per->y);

        switch (evento.keyboard.keycode) {
        case ALLEGRO_KEY_W:
            move_personagem(jog->per, DIRE_CIMA);
            avisa_direcao(r, DIRE_CIMA);
            break;
        case ALLEGRO_KEY_A:
            move_personagem(jog->per, DIRE_ESQ);
            avisa_direcao(r, DIRE_ESQ);
            break;
        case ALLEGRO_KEY_S:
            move_personagem(jog->per, DIRE_BAIXO);
            avisa_direcao(r, DIRE_BAIXO);
            break;
        case ALLEGRO_KEY_D:
            move_personagem(jog->per, DIRE_DIR);
            avisa_direcao(r, DIRE_DIR);
            break;
        default:
            break;
        }

        //jog->pode_andar = 0;
        //envia mensagem q andou
    }
}

int mostra_jogo(Interface *inter, Jogo *jog, Rede *r, bool serv) {
    int retorno;

    if(inter->fechou)
        return SAIR;

    retorno = JOGO;

    if(serv)
        escolhe_posicoes(r, jog->mapa, jog->per);
    else
        recebe_pos_inicial(r, jog->per);

    ALLEGRO_EVENT evento;
    inicia_tempo(inter);
    al_wait_for_event(inter->fila, &evento);

    while(evento.type != ALLEGRO_EVENT_DISPLAY_CLOSE && retorno == JOGO) {
        if (evento.type == ALLEGRO_EVENT_TIMER) {
            desenha_mapa(jog->mapa, serv);
            desenha_personagem(jog->per);
            al_flip_display ();
        }

        pausa_tempo(inter);
        if(serv) 
            recebe_direcao(r, jog->mapa, jog->per);
        else
            atualiza_posicao(jog, r, evento);
        retoma_tempo(inter);

        if(!serv && tem_tesouro_enterrado(jog->mapa, jog->per->x, jog->per->y)) {
            insere_tesouro(jog->mapa, 0, jog->per->x, jog->per->y);
            retorno = TESOURO_TELA;
        }

        else if(!serv && mapa_limpo(jog->mapa)) {
            retorno = FIM;
        }

        al_wait_for_event (inter->fila, &evento);
    }

    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        inter->fechou = 1;

    return retorno;
}