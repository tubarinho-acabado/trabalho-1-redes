#include <stdlib.h>
#include <stdio.h>
#include "../headers/redes/mensagem.h"

int main() {
    unsigned char dados[16];

    for(unsigned char i = 0; i < 16; i++)
        dados[i] = 0;

    dados[0] = 224;
    dados[1] = 187;
    dados[2] = 203;
    dados[3] = 122;
    dados[4] = 176;
    dados[5] = 212;
    dados[6] = 178;
    dados[7] = 113;
    Mensagem *msg = cria_mensagem(16, 1, 10, 0, dados);

    unsigned char *buffer = escreve_mensagem(msg);

    Mensagem *msg2 = decodifica_mensagem(buffer);

    destroi_mensagem(msg);

    printf("tam = %d \nseq = %d \ntipo = %d\ncheckSum = %d \n\n", 
           msg2->tam, msg2->seq, msg2->tipo, msg2->checkSum);

    for(unsigned char i = 0; i < msg2->tam; i++) 
        printf("dados[%d] = %d\n", i, msg2->dados[i]);

    /*unsigned char result = calcula_checkSum(msg, buffer);

    printf("\nResultado: ");
    imprime_binario(result);

    buffer[3] = result;

    if(verifica_checkSum(msg, buffer))
        printf("\n Funcionou :D\n");*/
}