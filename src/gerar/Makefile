CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h ../estado.c ../estado.h ../verifica.c ../verifica.h ../extras.c ../extras.h ../ficheiro.c ../ficheiro.h gerar.c gerar.h Makefile
EXECUTAVEL=gerar

$(EXECUTAVEL): gerar.o ../verifica.o ../estado.o
	cc -o $(EXECUTAVEL) gerar.o ../verifica.o ../estado.o


gerar.o:    gerar.c gerar.h ../verifica.h
