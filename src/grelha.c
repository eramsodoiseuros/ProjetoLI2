/**
@file grelha.c
Contém as funções relativas à grelha e ao ESTADO
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "ficheiro.h"
#include "verifica.h"
#include "extras.h"

#define MAX_BUFFER	  10240

/**
Função que inicializa o estado
@returns Um novo estado
*/
ESTADO inicializarEstado() {

	ESTADO e; e.num_lins = 4; e.num_cols = 4;
	iniciaVazia(&e);

	e.grelha[1][0] = BLOQUEADA;
	e.grelha[1][1] = FIXO_O;

	return e;
}

/**
Lê o estado a partir da variável de ambiente QUERY_STR. Caso não seja passado um valor, chama a função loadFile
@param args O valor da variável (o que é passado depois de ? no URL)
@returns O estado
*/
ESTADO ler_estado(char *args) {

	if(args == NULL || strlen(args) == 0) return inicializarEstado();

	char *args1 = &args[1], facil[MAX_BUFFER], medio[MAX_BUFFER], dificl[MAX_BUFFER], voltar[MAX_BUFFER], sancora[MAX_BUFFER], rancora[MAX_BUFFER];

	sprintf(facil, "1%s", args1);
	sprintf(medio, "2%s", args1);
	sprintf(dificl, "3%s", args1);

		if(strcmp(args, facil) == 0){
			args = "1"; return loadFile(args);
		} else if(strcmp(args, medio) == 0){
		 	args = "2"; return loadFile(args);
		} else if(strcmp(args, dificl) == 0){
		 	args = "3"; return loadFile(args);
		}

	sprintf(voltar, "v%s", args1);
	sprintf(sancora, "a%s", args1);
	sprintf(rancora, "r%s", args1);

	if(strcmp(args, voltar) == 0) return str2estado(args1);
	else if(strcmp(args, sancora) == 0) return str2estado(args1);
	else if(strcmp(args, rancora) == 0) return str2estado(args1);
	else return str2estado(args);
}

/**
Esta função é a responsãvel pela lógica do jogo em aspetos como saber se regressa de ancora ou se coloca ancora.
**/
void SetRegressaAncora(char *utilizador, int tabuleiro, int jogada, int ancora, char *s, int valorAncora, char *setAncora, char *regressaDeAncora){

	if(strcmp(setAncora, s) == 0 && ancora >= 1){
		jogada--;
		atualizaUserFile(utilizador, tabuleiro, jogada, jogada);
	}

	if(strcmp(regressaDeAncora, s) == 0 && ancora >= 1){
		jogada--;
		atualizaUserFile(utilizador, tabuleiro, ancora, valorAncora);
	}
}

/**
Esta função é a intermediária entre a função grelha e as funções reponsáveis por cada elemento.
**/
void printGrelha(char *utilizador, int tabuleiro, int jogada, int ancora, char *s, char *buf){
	char *estadoaux = &s[1];
	char auxLine[MAX_BUFFER], goLine[MAX_BUFFER], setAncora[MAX_BUFFER], voltar[MAX_BUFFER], regressaDeAncora[MAX_BUFFER];

	if(strcmp(utilizador, estadoaux) == 0 && jogada > 1){
		FILE *userfile; userfile = fopen(buf, "r"); int k = 0;
	    while (fgets(goLine, sizeof(goLine), userfile) && k <= jogada) k++;
    	s = goLine;
	}

	snprintf(setAncora, sizeof(setAncora), "a%s", estadoaux);
	sprintf(voltar, "v%s", estadoaux);
	sprintf(regressaDeAncora, "r%s", estadoaux);

	if(strcmp(voltar, s) == 0 && jogada > 1) {

		jogada = jogada - 2;
		atualizaUserFile(utilizador, tabuleiro, jogada, ancora);
		FILE* auxFile = fopen(buf, "r+"); int j = 0;
	    while (fgets(auxLine, sizeof(auxLine), auxFile) && j <= jogada) j++;
    	fclose(auxFile);
    	s = auxLine;
	} else if(strcmp(s,voltar) == 0 && jogada == 0){
		jogada = 1;
		atualizaUserFile(utilizador, tabuleiro, jogada, ancora);
		s = estadoaux;
	} else {
		FILE *userfile;
		userfile = fopen(buf, "a");

		if(strcmp(voltar, s) == 0){

			ESTADO a = str2estado(&s[1]);
			a.ancora = ancora;
			char *estadoComAncora = estado2str(a);
			fprintf(userfile, "%s\n", estadoComAncora);
		} else if(strcmp(setAncora, s) == 0){

			ESTADO a = str2estado(&s[1]);
			a.ancora = jogada;
			char *estadoComAncora = estado2str(a);
			fprintf(userfile, "%s\n", estadoComAncora);
		} else if(strcmp(regressaDeAncora, s) == 0){
			fprintf(userfile, "%s\n", &s[1]);
		} else {
			if(jogada > 1){
				ESTADO a = str2estado(s);
				a.ancora = ancora;
				char *estadoComAncora = estado2str(a);
				fprintf(userfile, "%s\n", estadoComAncora);
			} else fprintf(userfile, "%s\n", s);
		}
		fclose(userfile);
	}

	ESTADO e = ler_estado(s);
	int valorAncora = getAncora(jogada, utilizador);
	SetRegressaAncora(utilizador, tabuleiro, jogada, ancora, s, valorAncora, setAncora, regressaDeAncora);
    printGame(s, tabuleiro, jogada, valorAncora, e, setAncora, regressaDeAncora, buf);
}

/**
Esta função é a responsável por imprimir no ecrã a grelha para jogar e todos os respetivos elementos. Para isso receb como parâmetros o nome do utilizador, o tabuleiro, a jogada atual e a ancora mais recente.
@returns 0
**/
int grelha(char *utilizador, int tabuleiro, int jogada, int ancora){

	char *s = getenv("QUERY_STRING");
	char userfile[MAX_BUFFER]; 
	
	snprintf(userfile, sizeof(userfile), "/var/www/html/users/%s.txt", utilizador);

	if(valida(ler_estado(s)) == 2) printGrelha(utilizador, tabuleiro, jogada, ancora, s, userfile);
	else if(valida(ler_estado(s)) == 1) mensagemFinal(utilizador, tabuleiro, jogada, 1);
	else if(valida(ler_estado(s)) == 0) mensagemFinal(utilizador, tabuleiro, jogada, 0);

	return 0;
}