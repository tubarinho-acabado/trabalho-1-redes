CFLAGS = -g
LDLIBS = `pkg-config allegro-5 allegro_main-5 allegro_image-5 allegro_primitives-5 --libs --cflags`
CC = gcc

teste_arquivo: objs/teste_arquivo.o objs/arquivo.o objs/conexao.o objs/mensagem.o
	$(CC) -o teste_arquivo objs/teste_arquivo.o objs/arquivo.o objs/conexao.o objs/mensagem.o

teste_checksum: objs/teste_checksum.o objs/conexao.o objs/mensagem.o
	$(CC) -o teste_checksum objs/teste_checksum.o objs/conexao.o objs/mensagem.o

teste1: objs/teste1.o objs/desenha.o objs/mapa.o objs/personagem.o 
	$(CC) -o teste1 objs/teste1.o objs/teste1.o objs/mapa.o objs/personagem.o $(LDLIBS)

teste2: objs/teste2.o objs/botao.o objs/conexao.o objs/desenha.o objs/fim.o objs/inicio.o objs/interface.o objs/jogo.o objs/mapa.o objs/mensagem.o objs/personagem.o objs/rede.o objs/tela_tesouro.o
	$(CC) -o teste2 objs/teste2.o objs/botao.o objs/conexao.o objs/desenha.o objs/fim.o objs/inicio.o objs/interface.o objs/jogo.o objs/mapa.o objs/mensagem.o objs/personagem.o objs/rede.o objs/tela_tesouro.o $(LDLIBS)

teste_cabo: objs/teste_cabo.o objs/conexao.o objs/mensagem.o
	$(CC) -o teste_cabo objs/teste_cabo.o objs/conexao.o objs/mensagem.o

objs/teste_arquivo.o: sources/teste_arquivo.c
	$(CC) -c $(CFLAGS) sources/teste_arquivo.c -o objs/teste_arquivo.o

objs/teste_checksum.o: sources/teste_checksum.c
	$(CC) -c $(CFLAGS) sources/teste_checksum.c -o objs/teste_checksum.o

objs/teste1.o: sources/teste1.c
	$(CC) -c $(CFLAGS) sources/teste1.c -o objs/teste1.o

objs/teste2.o: sources/teste2.c
	$(CC) -c $(CFLAGS) sources/teste2.c -o objs/teste2.o

objs/teste_cabo.o: sources/teste_cabo.c
	$(CC) -c $(CFLAGS) sources/teste_cabo.c -o objs/teste_cabo.o

objs/arquivo.o: headers/redes/arquivo.h sources/redes/arquivo.c
	$(CC) -c $(CFLAGS) sources/redes/arquivo.c -o objs/arquivo.o

objs/botao.o: headers/jogo/botao.h sources/jogo/botao.c
	$(CC) -c $(CFLAGS) sources/jogo/botao.c -o objs/botao.o

objs/conexao.o: headers/redes/conexao.h sources/redes/conexao.c
	$(CC) -c $(CFLAGS) sources/redes/conexao.c -o objs/conexao.o

objs/desenha.o: headers/graficos/desenha.h sources/graficos/desenha.c
	$(CC) -c $(CFLAGS) sources/graficos/desenha.c -o objs/desenha.o

objs/fim.o: headers/jogo/fim.h sources/jogo/fim.c
	$(CC) -c $(CFLAGS) sources/jogo/fim.c -o objs/fim.o

objs/inicio.o: headers/jogo/inicio.h sources/jogo/inicio.c
	$(CC) -c $(CFLAGS) sources/jogo/inicio.c -o objs/inicio.o

objs/interface.o: headers/jogo/interface.h sources/jogo/interface.c
	$(CC) -c $(CFLAGS) sources/jogo/interface.c -o objs/interface.o

objs/jogo.o: headers/jogo/jogo.h sources/jogo/jogo.c
	$(CC) -c $(CFLAGS) sources/jogo/jogo.c -o objs/jogo.o

objs/mapa.o: headers/graficos/imagens.h headers/jogo/mapa.h sources/jogo/mapa.c
	$(CC) -c $(CFLAGS) sources/jogo/mapa.c -o objs/mapa.o

objs/mensagem.o: headers/redes/mensagem.h sources/redes/mensagem.c
	$(CC) -c $(CFLAGS) sources/redes/mensagem.c -o objs/mensagem.o

objs/personagem.o: headers/graficos/imagens.h headers/jogo/personagem.h sources/jogo/personagem.c
	$(CC) -c $(CFLAGS) sources/jogo/personagem.c -o objs/personagem.o

objs/rede.o: headers/redes/rede.h sources/redes/rede.c
	$(CC) -c $(CFLAGS) sources/redes/rede.c -o objs/rede.o

objs/registro.o: headers/redes/registro.h sources/redes/registro.c
	$(CC) -c $(CFLAGS) sources/redes/registro.c -o objs/registro.o

objs/tela_tesouro.o: headers/jogo/tela_tesouro.h sources/jogo/tela_tesouro.c
	$(CC) -c $(CFLAGS) sources/jogo/tela_tesouro.c -o objs/tela_tesouro.o

clean: 
	-rm -f *~ *.o objs/*.o