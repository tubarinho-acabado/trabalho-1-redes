#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include "../headers/graficos/imagens.h"
#include "../headers/jogo/mapa.h"
#include "../headers/jogo/personagem.h"
#include "../headers/graficos/desenha.h"

#define TAM_TELA 640

int main() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
    ALLEGRO_DISPLAY *tela = al_create_display(TAM_TELA, TAM_TELA);
    ALLEGRO_TIMER *tempo = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT evento;

    al_register_event_source(fila, al_get_display_event_source(tela));
    al_register_event_source(fila, al_get_timer_event_source(tempo));
    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_mouse_event_source());
    al_start_timer(tempo);

    Mapa *m = cria_mapa(true);
    Personagem *p = cria_personagem(6, 6);

    if(m == NULL || p == NULL)
        return 1;

    al_set_display_icon(tela, p->desenho);

    al_wait_for_event(fila, &evento);
    while(evento.type != ALLEGRO_EVENT_DISPLAY_CLOSE) {

        if(evento.type == 12) {
            printf("asdvcxdfghjkjgf\n");
            printf("%d %d\n", p->x, p->y);
            marca_presenca(m, p->x, p->y);
            switch (evento.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                move_personagem(p, CIMA);
                break;
            case ALLEGRO_KEY_A:
                move_personagem(p, ESQ);
                break;
            case ALLEGRO_KEY_S:
                move_personagem(p, BAIXO);
                break;
            case ALLEGRO_KEY_D:
                move_personagem(p, DIR);
                break;
            default:
                break;
            }
        }

        else if(evento.type == 30) {
            desenha_mapa(m);
            desenha_personagem(p);
            al_flip_display();
        }

        al_wait_for_event(fila, &evento);
    }

    //destroi_mapa(m);
    //desaloca_personagem(p);

    al_destroy_event_queue(fila);	
    al_destroy_display(tela);

    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_system();
}