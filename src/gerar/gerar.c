/**
@file gerar.c
Ficheiro que contém o código relativo a gerar tabuleiros
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../cgi.h"
#include "../estado.h"
#include "../verifica.h"
#include "../ficheiro.h"
#include "../extras.h"
#include "../verifica.h"

#define MAX_BUFFER	  10240
#define GRELHA		  4
#define TAM			  40

/**
Função que determina se a grelha está cheia.
*/
int cheia(const ESTADO *e){
	int r = 1;
	for(int l = 0; l <= e->num_lins; l++){
		for(int c = 0; c <= e->num_cols; c++){
			if(e->grelha[c][l]==VAZIA) r = 0;
		}
	}
	return r;
}

/**
Função que determina se uma posição da grelha é conflituosa.
*/
int conflito(ESTADO *e, int c, int l){
	int r = 0;
	if(!diagonais(e)){
		e->grelha[c][l] = FIXO_X;
		if(diagonais(e)){
			e->grelha[c][l] = FIXO_O;
			if(diagonais(e)) r = 1;
		}
	}
	if(!horizontais(e)){
		e->grelha[c][l] = FIXO_X;
		if(horizontais(e)){
			e->grelha[c][l] = FIXO_O;
			if(horizontais(e)) r = 1;
		}
	}
	if(!verticais(e)){
		e->grelha[c][l] = FIXO_X;
		if(verticais(e)){
			e->grelha[c][l] = FIXO_O;
			if(verticais(e)) r = 1;
		}
	}
	if(itsX(e,c,l) && itsO(e,c,l)) r = 1;
	if(itsXX(e,c,l) && itsOO(e,c,l)) r = 1;
	return r;
}

/**
Função que verifica se existem 3 peças iguais seguidas.
*/
int itsT(ESTADO *e, int c, int l){
	int r = 0;
	if((e->grelha[c][l] == e->grelha[c+1][l]) && (e->grelha[c][l] == e->grelha[c-1][l])) r = 1;
	if((e->grelha[c][l] == e->grelha[c][l+1]) && (e->grelha[c][l] == e->grelha[c][l-1])) r = 1;
	if((e->grelha[c][l] == e->grelha[c+1][l+1]) && (e->grelha[c][l] == e->grelha[c-1][l-1])) r = 1;
	if((e->grelha[c][l] == e->grelha[c+1][l-1]) && (e->grelha[c][l] == e->grelha[c-1][l+1])) r = 1;
	return r;
}
/**
Função que bloqueia as peças que tornam o tabuleiro invalido.
*/
void bloqueia(ESTADO *e){

	for(int l = 0; l <= e->num_lins; l++){
		for(int c = 0; c <= e->num_cols; c++){
			if(conflito(e, c, l)) e->grelha[c][l] = BLOQUEADA;
			else if(cheia(e))break;
			else if(itsO(e, c, l)) e->grelha[c][l] = FIXO_O;
			else if(itsXX(e, c, l)) e->grelha[c][l] = FIXO_O;
			else if(itsX(e, c, l)) e->grelha[c][l] = FIXO_X;
			else if(itsOO(e, c, l)) e->grelha[c][l] = FIXO_X;
		}
	}
	for(int l = 0; l <= e->num_lins; l++){
		for(int c = 0; c <= e->num_cols; c++){
			if(itsT(e,c,l)) e->grelha[c][l] = BLOQUEADA;		
		}
	}
}

/**
\brief Função que verifica se já existem peças para bloquear:
@param estado
@returns 0 se a grelha não é valida,
@returns 1 se a grelha está dentro do padrão,
*/
int vBloq(const ESTADO *e){
	
	if(horizontais(e) + verticais(e) + diagonais(e) >= 1) return 0;
	else if(cheia(e)) return 0;	
	else return 1;
}

/**
Função que preenche uma grelha vazia.
*/
void preenche(ESTADO *e){
	time_t t; srand((unsigned) time(&t)); int c1, l1;
	int colunas = e->num_cols, linhas = e->num_lins;
	iniciaVazia(e);
	while( vBloq(e) ){
		c1 = rand() % colunas; l1 = rand() % linhas;
		if(e->grelha[c1][l1] == VAZIA)
			e->grelha[c1][l1] = FIXO_X;
	}
	bloqueia(e); printEstado(e); printf("Solução\n\n");
}


/**
Função que a um tabuleiro preenchido, retira peças até se tornar uma grelha semi-preenchida de solução unica.
*/
void geraFacil(ESTADO *e){
	ESTADO e1; memcpy(&e1,e,sizeof(ESTADO));
	for(int l = 0; l <= e->num_lins; l++){
		for(int c = 0; c <= e->num_cols; c++){
			if(e->grelha[c][l] == BLOQUEADA) break;
			if(itsOO(e, c, l)) {e->grelha[c][l] = VAZIA;}
			else if(itsXX(e, c, l)) {e->grelha[c][l] = VAZIA;}
		}
	}
	// se o estado não for alterado, a Função opta por outra estratégia. 
	if(strcmp( estado2str(e1), estado2str(*e) ) == 0){
		for(int l = 0; l <= e->num_lins; l++){
			for(int c = 0; c <= e->num_cols; c++){
				if(e->grelha[c][l] == BLOQUEADA) break;
				if(itsO(e, c, l)) e->grelha[c][l] = VAZIA;
				else if(itsX(e, c, l)) e->grelha[c][l] = VAZIA;
			}
		}
	} printEstado(e);
} // Grelha cuja solução se obtem atraves das ajudas

/**
Função que a um tabuleiro preenchido, retira peças até se tornar uma grelha semi-preenchida de solução unica.
*/
void geraDificil(ESTADO *e){
	printEstado(e); // Grelha cuja solução se obtem atraves das ajudas, mas também recorrendo à tentativa erro.
}

/**
Função main que combina todas as funcionalidades de gerar grelhas.
@returns 0 se a grelha for gerada corretamente,
@returns 1 se os parametros forem mal introduzidos.
*/
int main(int argc, char *argv[]){

	int linhas, colunas, dificuldade;
	if(argc != 4){
		printf("Parâmetros incorretos.\n");
		return 1;
	}
	sscanf(argv[1], "%d", &dificuldade);
	sscanf(argv[2], "%d", &linhas);
	sscanf(argv[3], "%d", &colunas);

	printf("%d %d\n", linhas, colunas);
	ESTADO e; e.num_lins = linhas-1; e.num_cols = colunas-1;
	preenche(&e);
	if(dificuldade == 1) geraFacil(&e);
	else if(dificuldade == 2) geraDificil(&e);
	else {
		printf("\nA dificuldade é um número de 1 a 2, sendo 1 Fácil e 2 Dificil.\n");
		printf("\nVolte a tentar gerar o tabuleiro pretendido.\n");
	}
	return 0;
}
