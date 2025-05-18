#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include "../../headers/redes/conexao.h"
#include "../../headers/redes/mensagem.h"

Mensagem *cria_mensagem(unsigned char tam, unsigned char seq, unsigned char tipo, unsigned char checkSum, unsigned char *dados) {
    Mensagem *msg;

    msg = (Mensagem *) malloc(sizeof(Mensagem));
    if (msg == NULL) {
        printf("Algo deu errado na criacao da mensagem :(\n");
        return NULL;
    }

    msg->tam = tam;
    msg->seq = seq;
    msg->tipo = tipo;
    msg->dados = dados;
    msg->checkSum = checkSum;

    return msg;
}

void destroi_mensagem(Mensagem *msg) {
    if(msg != NULL)
        free(msg);
}

Mensagem *decodifica_mensagem(unsigned char *buffer) {
    unsigned char tam = buffer[1] / 2;

    unsigned char *dados = NULL;
    if(tam > 0) {
        dados = (unsigned char *) malloc(sizeof(unsigned char) * tam);
        if(dados == NULL)
            return NULL;

        for(unsigned char i = 0; i < tam; i++)
            dados[i] = buffer[i + 4];
    }
    
    unsigned char seq = (buffer[1] % 2) + (buffer[2] / 16);
    unsigned char tipo = buffer[2] % 16;

    return cria_mensagem(tam, seq, tipo, buffer[3], dados);
}

void imprime_binario(unsigned char num) {
    int pow = 128;

    for(int i = 0; i <= 7; i++) {
        printf("%d", (num / pow) % 2);
        pow = pow / 2;
    }

    printf("\n");
}

bool verifica_checkSum(Mensagem *msg, unsigned char *buffer) {
    int tam_buffer = 4 + (int) msg->tam;
    unsigned char soma = 0;

    for(int i = 1; i < tam_buffer; i++) {

        //printf("Buffer em %d: ", i);

        //imprime_binario(buffer[i]);
        soma += buffer[i];

        //printf("Soma: (%d) ", soma);
        //imprime_binario(soma);
        //printf("\n");
    }

    //printf("Resultado verificação: %d\n", soma);
    return !soma;
}

unsigned char calcula_checkSum(Mensagem *msg, unsigned char *buffer) {
    int tam_buffer = 4 + (int) msg->tam;
    unsigned char soma = 0;

    for(int i = 1; i < tam_buffer; i++) {

        //printf("Buffer em %d: ", i);

        //imprime_binario(buffer[i]);
        soma += buffer[i];

        //printf("Soma: (%d) ", soma);
        //imprime_binario(soma);
        //printf("\n");
    }

    return 256 - soma;
}

bool verifica_sequencia(Mensagem *msg_atual, Mensagem *ult_recebida) {
    
}

/*bool tem_erro(Mensagem *msg_atual, Mensagem *ult_recebida) {
    if(!verifica_checkSum || !verifica_sequencia)

}*/

unsigned char *escreve_mensagem(Mensagem *msg, int *tam_buffer) {
    unsigned char *buffer;

    unsigned char tam = MIN_DADOS + 4;
    if(msg->tam + 4 > tam)
        tam = msg->tam + 4;

    buffer = calloc(tam, sizeof(unsigned char));
    if(buffer == NULL) return NULL;
    *tam_buffer = tam;

    buffer[0] = 126;
    buffer[1] = (msg->tam * 2) + (msg->seq / 128);
    buffer[2] = (msg->tipo % 16) + ((msg->seq % 16) * 16);
    buffer[3] = 0;

    for(int i = 0; i < msg->tam; i++) {
        buffer[i + 4] = msg->dados[i];
    }

    buffer[3] = calcula_checkSum(msg, buffer);

    return buffer;
}

int envia_mensagem(Mensagem *msg, int soquete) {
    int tam_buffer;

    unsigned char *buffer = escreve_mensagem(msg, &tam_buffer);
    if(buffer == NULL) return 1;

    if(msg->checkSum == 0)
        buffer[3] = calcula_checkSum(msg, buffer);

    printf("%d %d\n", soquete, tam_buffer);

    return send(soquete, buffer, tam_buffer, 0) >= 0;
}

int protocolo_e_valido(char* buffer, int tamanho_buffer) {
    if (tamanho_buffer <= 0) {
        return 0;
    }

    return buffer[0] == 126;
}

// retorna -1 se deu timeout, ou quantidade de bytes lidos
int recebe_buffer(int soquete, char* buffer, int tamanho_buffer) {
    long long comeco = timestamp();
    struct timeval timeout = { .tv_sec = TIMEOUT/1000, .tv_usec = (TIMEOUT%1000) * 1000 };
    setsockopt(soquete, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));
    int bytes_lidos;
    do {
        bytes_lidos = recv(soquete, buffer, tamanho_buffer, 0);
        if (protocolo_e_valido(buffer, bytes_lidos)) { return bytes_lidos; }
    } while (timestamp() - comeco <= TIMEOUT);
    return -1;
}

//  0: tudo certo
// -1: mensagem errada (nack)
//  1: algum outro erro
int recebe_mensagem(int soquete, Mensagem **msg) {
    *msg = NULL;

    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char) * (MAX_DADOS + 4));
    if(buffer == NULL)
        return 1;

    if(recebe_buffer(soquete, buffer, MAX_DADOS + 4) < 0)
        return 1;

    *msg = decodifica_mensagem(buffer);
    if(*msg == NULL)
        return 1;

    if(verifica_checkSum(*msg, buffer)) {
        destroi_mensagem(*msg);
        *msg = NULL;
        free(buffer);
        return -1;
    }
    free(buffer);
    return 0;
}

/*void envia_mensagem(Mensagem *msg, int soquete) {
    unsigned char *buffer = escreve_mensagem(msg);
    if(buffer == NULL) return 1;

    send(soquete, buffer, msg->tam + 4, 0);
}*/