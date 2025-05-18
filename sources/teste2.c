#include <stdio.h>
#include <string.h>
#include "../headers/jogo/interface.h"
#include "../headers/jogo/inicio.h"
#include "../headers/jogo/jogo.h"
#include "../headers/jogo/tela_tesouro.h"
#include "../headers/jogo/fim.h"
#include "../headers/jogo/mapa.h"
#include "../headers/jogo/personagem.h"


int main(int argc, char **argv) {
    if(argc <= 1) {
        printf("Informe -serv para servidor e -cli para cliente\n");
        return 1;
    }

    bool serv;
    if(!strcmp(argv[1], "-serv")) 
        serv = 1;
    else if(!strcmp(argv[1], "-cli"))
        serv = 0;
    else {
        printf("Informe -serv para servidor e -cli para cliente\n");
        return 1;
    }
    
    Rede *rede = cria_rede();
    Interface *inter = cria_interface();
    Inicio *ini = cria_inicio();
    Jogo *jog = cria_jogo();
    Tela_tesouro *tes = cria_tela_tesouro();
    Fim *fim = cria_fim();

    mostra_icone(inter);

    int acao;
    if(!serv)
        acao = INICIO;
    else
        acao = JOGO;
    
    while(!inter->fechou) {
        switch (acao) {
        case INICIO:
            acao = mostra_inicio (inter, ini, jog->mapa, jog->per);
            break;
        case JOGO:
            acao = mostra_jogo(inter, jog, rede, serv);
            break;
        case TESOURO_TELA:
            acao = mostra_tela_tesouro(inter, tes, jog->mapa, jog->per);
            break;
        case FIM:
            acao = mostra_fim(inter, fim);
            break;
        case SAIR:
            inter->fechou = 1;
            break;
        default:
            break;
        }
    }

  destroi_inicio(ini);
  destroi_jogo(jog);
  destroi_tela_tesouro(tes);
  destroi_interface(inter);
  destroi_fim(fim);
  destroi_rede(rede);
}