#include <stdlib.h>
#include <stdio.h>
#include "../headers/redes/arquivo.h"
#include "../headers/redes/conexao.h"
#include "../headers/redes/mensagem.h"

#define CAMINHO_ARQUIVO_TESTE "filme.mp4"

int main() {
    int serv;

    scanf("%d", &serv);
    int soquete = cria_raw_socket();

    if(serv == 1) {
        FILE *arq = fopen(CAMINHO_ARQUIVO_TESTE, "r+");
        if(arq == NULL)
            return 1;

        unsigned char tam = MAX_DADOS;
        while(tam == MAX_DADOS) {
            unsigned char seq = 0;
            unsigned char *dados = parte_do_arquivo(arq, &tam);
            if(dados == NULL)
                return 1;

            Mensagem *msg = cria_mensagem(tam, seq, 1, 0, dados);
            if(msg == NULL)
                return 1;

            seq++;
            seq = seq % 32;

            unsigned char *buffer = escreve_mensagem(msg);

            send(soquete, buffer, msg->tam + 4, 0);

            free(dados);
            destroi_mensagem(msg);
        }
        fclose(arq);
    }
    else {
        FILE *arq = fopen(CAMINHO_ARQUIVO_TESTE, "r+");
        if(arq == NULL)
            return 1;
        Mensagem *msg;
        
        do {
            unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * (MAX_DADOS + 4));
            if(buffer == NULL)
                return 1;

            recebe_mensagem(soquete, 300000000, buffer, MAX_DADOS + 4);
            destroi_mensagem(msg);
            msg = decodifica_mensagem(buffer);
            if(msg == NULL)
                    return 1;

            if(verifica_checkSum(msg, buffer))
                fwrite(msg->dados, sizeof(unsigned char), msg->tam, arq);

            free(buffer);

        } while(msg->tam == MAX_DADOS);

        fclose(arq);
    }

    destroi_raw_socket(soquete);
}