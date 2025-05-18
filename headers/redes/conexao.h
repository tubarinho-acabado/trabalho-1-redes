#ifndef __conexao__
#define __conexao__

#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <net/if.h>

#define TIMEOUT 3000

int cria_raw_socket();

void destroi_raw_socket(int soquete);

long long timestamp();

#endif