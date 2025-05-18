#include <stdio.h>
#include <stdbool.h>
#include "../headers/redes/mensagem.h"
#include "../headers/redes/conexao.h"

int main() {
    char *nome;
    int serv;
    unsigned char msg[14];

    scanf("%d", &serv);
    int soquete = cria_raw_socket();
    if(serv == 1) {
        recebe_mensagem(soquete, TIMEOUT, msg, 14);
        printf("%d\n", (int) msg[1]);
    }
    else {
        msg[0] = 126;
        msg[1] = 0x88;
        msg[2] = 7;
        send(soquete, msg, 14, 0);
    }

    destroi_raw_socket(soquete);
}