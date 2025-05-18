#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/redes/conexao.h"

char *nome_interface() {
    char linha[256];
    char *nome = (char *) malloc(sizeof(char) * 40);

    if(nome == NULL)
        return NULL;

    char *busca;

    system("ip addr > interfaces_rede.txt");

    FILE *interfaces = fopen("interfaces_rede.txt", "r+");

    do {
        fscanf(interfaces, "%[^\n]", linha);
        fgetc(interfaces);
        busca = strstr(linha, ": e");
    } while(busca == NULL);

    busca += 2;
    int i = 0;
    while(busca[0] != ':') {
        nome[i] = busca[0];
        i++;
        busca++;
    }

    fclose(interfaces);
    system("rm interfaces_rede.txt");
    return nome;
}

int cria_raw_socket() {
    // Cria arquivo para o socket sem qualquer protocolo
    int soquete = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (soquete == -1) {
        fprintf(stderr, "Erro ao criar socket: Verifique se você é root!\n");
        exit(-1);
    }
 
    int ifindex = if_nametoindex(nome_interface());
 
    struct sockaddr_ll endereco = {0};
    endereco.sll_family = AF_PACKET;
    endereco.sll_protocol = htons(ETH_P_ALL);
    endereco.sll_ifindex = ifindex;
    // Inicializa socket
    if (bind(soquete, (struct sockaddr*) &endereco, sizeof(endereco)) == -1) {
        fprintf(stderr, "Erro ao fazer bind no socket\n");
        exit(-1);
    }
 
    struct packet_mreq mr = {0};
    mr.mr_ifindex = ifindex;
    mr.mr_type = PACKET_MR_PROMISC;
    // Não joga fora o que identifica como lixo: Modo promíscuo
    if (setsockopt(soquete, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) == -1) {
        fprintf(stderr, "Erro ao fazer setsockopt: "
            "Verifique se a interface de rede foi especificada corretamente.\n");
        exit(-1);
    }
 
    return soquete;
}

void destroi_raw_socket(int soquete) {
    shutdown(soquete, 2);
}

// usando long long pra (tentar) sobreviver ao ano 2038
long long timestamp() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec*1000 + tp.tv_usec/1000;
}