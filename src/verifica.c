/**
@file verfica.c
Contém as funções de validação do jogo
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"


/**
Função que verifica a condição diagonal do Jogo:
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida.
@returns 3 se algo correr muito mal.
*/
int diagonais(const ESTADO *e){

	int valor = 3;
	for (int c = 1; c <= (e->num_cols - 1); c++){
		for (int l = 1; l <= (e->num_lins - 1); l++){
			if (( ((e->grelha[c][l]     == SOL_X || e->grelha[c][l]     == FIXO_X)    &&
				   (e->grelha[c+1][l+1] == SOL_X || e->grelha[c+1][l+1] == FIXO_X)    &&
				   (e->grelha[c-1][l-1] == SOL_X || e->grelha[c-1][l-1] == FIXO_X))   ||
				  ((e->grelha[c][l]     == SOL_O || e->grelha[c][l]     == FIXO_O)    &&
				   (e->grelha[c+1][l+1] == SOL_O || e->grelha[c+1][l+1] == FIXO_O)    &&
				   (e->grelha[c-1][l-1] == SOL_O || e->grelha[c-1][l-1] == FIXO_O)) ) &&
				e->grelha[c][l] != VAZIA && e->grelha[c][l] != BLOQUEADA) {valor = 1; break;}
			else if (( ((e->grelha[c][l]     == SOL_X || e->grelha[c][l]     == FIXO_X)    &&
				   		(e->grelha[c+1][l-1] == SOL_X || e->grelha[c+1][l-1] == FIXO_X)    &&
				 		(e->grelha[c-1][l+1] == SOL_X || e->grelha[c-1][l+1] == FIXO_X))   ||
				  	   ((e->grelha[c][l]     == SOL_O || e->grelha[c][l]     == FIXO_O)    &&
				   		(e->grelha[c+1][l-1] == SOL_O || e->grelha[c+1][l-1] == FIXO_O)    &&
				   		(e->grelha[c-1][l+1] == SOL_O || e->grelha[c-1][l+1] == FIXO_O)) ) &&
				e->grelha[c][l] != VAZIA && e->grelha[c][l] != BLOQUEADA) {valor = 1; break;}
			else valor = 0;
		} if(valor == 1) break;
	}
	return valor;
}

/**
Função que verifica a condição horizontal do Jogo:
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida.
@returns 3 se algo correr muito mal.
*/
int horizontais(const ESTADO *e){

	int valor = 3;
	for (int c = 1; c <= (e->num_cols - 1); c++){
		for (int l = 0; l <= e->num_lins; l++){
			if (( ((e->grelha[c][l]   == SOL_X || e->grelha[c][l]   == FIXO_X)    &&
				   (e->grelha[c+1][l] == SOL_X || e->grelha[c+1][l] == FIXO_X)    &&
				   (e->grelha[c-1][l] == SOL_X || e->grelha[c][l-1] == FIXO_X))   ||
				  ((e->grelha[c][l]   == SOL_O || e->grelha[c][l]   == FIXO_O)    &&
				   (e->grelha[c+1][l] == SOL_O || e->grelha[c+1][l] == FIXO_O)    &&
				   (e->grelha[c-1][l] == SOL_O || e->grelha[c-1][l] == FIXO_O)) ) &&
				e->grelha[c][l] != VAZIA && e->grelha[c][l] != BLOQUEADA){valor = 1; break;}
			else valor = 0;
		} if(valor == 1) break;
	}
	return valor;
}

/**
Função que verifica a condição vertical do Jogo:
@returns 0 se a grelha está dentro do padrão,
@returns 1 se a grelha não é valida.
@returns 3 se algo correr muito mal.
*/
int verticais(const ESTADO *e){

	int valor = 3;
	for (int l = 1; l <= (e->num_lins - 1); l++){
		for (int c = 0; c <= e->num_cols; c++){
			if (( ((e->grelha[c][l]   == SOL_X || e->grelha[c][l]   == FIXO_X)    &&
				   (e->grelha[c][l+1] == SOL_X || e->grelha[c][l-1] == FIXO_X)    &&
				   (e->grelha[c][l-1] == SOL_X || e->grelha[c][l-1] == FIXO_X))   ||
				  ((e->grelha[c][l]   == SOL_O || e->grelha[c][l]   == FIXO_O)    &&
				   (e->grelha[c][l+1] == SOL_O || e->grelha[c][l+1] == FIXO_O)    &&
				   (e->grelha[c][l-1] == SOL_O || e->grelha[c][l-1] == FIXO_O)) ) &&
				e->grelha[c][l] != VAZIA && e->grelha[c][l] != BLOQUEADA) {valor = 1; break;}
			else valor = 0;
		} if(valor == 1) break;
	}
	return valor;
}

/**
Função que valida se um jogo acabou, classificando-o se tiver acabado
@returns 0 se a grelha está mal acabada,
@returns 1 se a grelha está bem acabada, 
@returns 2 se o jogo ainda estiver incompleto,
@returns 3 se algo correr muito mal.
*/
int valida(ESTADO e){
	
	int valor = 3; // se o valor 3 chegar ao fim, algo esta mal
	
	for(int l = 0; l <= e.num_lins; l++){
		for(int c = 0; c <= e.num_cols; c++){
			if (e.grelha[c][l] == VAZIA) {valor = 2; break;}
		} if(valor == 2) break;
	}

	if(valor == 2) return 2;
	else if(horizontais(&e) + verticais(&e) + diagonais(&e) >= 1) return 0;
	else return 1;
}

/**
Função que devolve se certa casa da grelha tem de ter um X.
@returns 0 se a casa não tem de ter um X,
@returns 1 se a casa tem de ter um X.
*/
int itsX(const ESTADO *e, int c, int l){
	if( ((e->grelha[c][l+1] == SOL_O || e->grelha[c][l+1] == FIXO_O)  &&
		 (e->grelha[c][l-1] == SOL_O || e->grelha[c][l-1] == FIXO_O)) ||         // checka vertical
	    ((e->grelha[c+1][l] == SOL_O || e->grelha[c+1][l] == FIXO_O)  &&
		 (e->grelha[c-1][l] == SOL_O || e->grelha[c-1][l] == FIXO_O)) ||        // checka horizontal
		((e->grelha[c+1][l+1] == SOL_O || e->grelha[c+1][l+1] == FIXO_O)  &&
		 (e->grelha[c-1][l-1] == SOL_O || e->grelha[c-1][l-1] == FIXO_O)) ||   // checka uma diagonal
		((e->grelha[c+1][l-1] == SOL_O || e->grelha[c+1][l-1] == FIXO_O)  &&
		 (e->grelha[c-1][l+1] == SOL_O || e->grelha[c-1][l+1] == FIXO_O)) )  // checka a ultima diagonal
		return 1;
	else return 0;
}

/**
Função que devolve se certa casa da grelha tem de ter um O.
@returns 0 se a casa não tem de ter um O,
@returns 1 se a casa tem de ter um O.
*/
int itsO(const ESTADO *e, int c, int l){
	if( ((e->grelha[c][l+1] == SOL_X || e->grelha[c][l+1] == FIXO_X)  &&
		 (e->grelha[c][l-1] == SOL_X || e->grelha[c][l-1] == FIXO_X)) ||         // checka vertical
	    ((e->grelha[c+1][l] == SOL_X || e->grelha[c+1][l] == FIXO_X)  &&
		 (e->grelha[c-1][l] == SOL_X || e->grelha[c-1][l] == FIXO_X)) ||        // checka horizontal
		((e->grelha[c+1][l+1] == SOL_X || e->grelha[c+1][l+1] == FIXO_X)  &&
		 (e->grelha[c-1][l-1] == SOL_X || e->grelha[c-1][l-1] == FIXO_X)) ||   // checka uma diagonal
		((e->grelha[c+1][l-1] == SOL_X || e->grelha[c+1][l-1] == FIXO_X)  &&
		 (e->grelha[c-1][l+1] == SOL_X || e->grelha[c-1][l+1] == FIXO_X)) )  // checka a ultima diagonal
		return 1;
	else return 0;
}

/**
Função que identifica se há dois X seguidos numa posição relativa à casa.
*/
int itsXX(const ESTADO *e, int c, int l){
	if( ((e->grelha[c][l+1] == SOL_X || e->grelha[c][l+1] == FIXO_X)  &&
		 (e->grelha[c][l+2] == SOL_X || e->grelha[c][l+2] == FIXO_X)) ||
		((e->grelha[c][l-1] == SOL_X || e->grelha[c][l-1] == FIXO_X)  &&
		 (e->grelha[c][l-2] == SOL_X || e->grelha[c][l-2] == FIXO_X)) ||         // checka vertical

	    ((e->grelha[c+1][l] == SOL_X || e->grelha[c+1][l] == FIXO_X)  &&
		 (e->grelha[c+2][l] == SOL_X || e->grelha[c+2][l] == FIXO_X)) ||
		((e->grelha[c-1][l] == SOL_X || e->grelha[c-1][l] == FIXO_X)  &&
		 (e->grelha[c-2][l] == SOL_X || e->grelha[c-2][l] == FIXO_X)) ||        // checka horizontal

		((e->grelha[c+1][l+1] == SOL_X || e->grelha[c+1][l+1] == FIXO_X)  &&
		 (e->grelha[c+2][l+2] == SOL_X || e->grelha[c+2][l+2] == FIXO_X)) ||
		((e->grelha[c-1][l+1] == SOL_X || e->grelha[c-1][l+1] == FIXO_X)  &&
		 (e->grelha[c-2][l+2] == SOL_X || e->grelha[c-2][l+1] == FIXO_X)) || 
		((e->grelha[c-1][l-1] == SOL_X || e->grelha[c-1][l-1] == FIXO_X)  &&
		 (e->grelha[c-2][l-2] == SOL_X || e->grelha[c-2][l-2] == FIXO_X)) ||
		((e->grelha[c+1][l-1] == SOL_X || e->grelha[c+1][l-1] == FIXO_X)  &&
		 (e->grelha[c+2][l-2] == SOL_X || e->grelha[c+2][l-2] == FIXO_X)) )    // checka diagonal
		 return 1;
	else return 0;
}

/**
Função que identifica se há dois O seguidos numa posição relativa à casa.
*/
int itsOO(const ESTADO *e, int c, int l){
	if( ((e->grelha[c][l+1] == SOL_O || e->grelha[c][l+1] == FIXO_O)  &&
		 (e->grelha[c][l+2] == SOL_O || e->grelha[c][l+2] == FIXO_O)) ||
		((e->grelha[c][l-1] == SOL_O || e->grelha[c][l-1] == FIXO_O)  &&
		 (e->grelha[c][l-2] == SOL_O || e->grelha[c][l-2] == FIXO_O)) ||         // checka vertical

	    ((e->grelha[c+1][l] == SOL_O || e->grelha[c+1][l] == FIXO_O)  &&
		 (e->grelha[c+2][l] == SOL_O || e->grelha[c+2][l] == FIXO_O)) ||
		((e->grelha[c-1][l] == SOL_O || e->grelha[c-1][l] == FIXO_O)  &&
		 (e->grelha[c-2][l] == SOL_O || e->grelha[c-2][l] == FIXO_O)) ||        // checka horizontal

		((e->grelha[c+1][l+1] == SOL_O || e->grelha[c+1][l+1] == FIXO_O)  &&
		 (e->grelha[c+2][l+2] == SOL_O || e->grelha[c+2][l+2] == FIXO_O)) ||
		((e->grelha[c-1][l+1] == SOL_O || e->grelha[c-1][l+1] == FIXO_O)  &&
		 (e->grelha[c-2][l+2] == SOL_O || e->grelha[c-2][l+1] == FIXO_O)) || 
		((e->grelha[c-1][l-1] == SOL_O || e->grelha[c-1][l-1] == FIXO_O)  &&
		 (e->grelha[c-2][l-2] == SOL_O || e->grelha[c-2][l-2] == FIXO_O)) ||
		((e->grelha[c+1][l-1] == SOL_O || e->grelha[c+1][l-1] == FIXO_O)  &&
		 (e->grelha[c+2][l-2] == SOL_O || e->grelha[c+2][l-2] == FIXO_O)) )    // checka diagonal
		 return 1;
	else return 0;
}

/**
Função que ajuda o jogador a preencher uma peça vazia, com base na função valida.
*/
ESTADO ajudas(ESTADO *e){

	int a = 1;
	if(e->numAjudas){
			for(int l = 0; l <= e->num_lins; l++){
				for(int c = 0; c <= e->num_cols; c++){
					if(e->grelha[c][l] == VAZIA){
						if(itsO(e, c, l)){e->grelha[c][l] = SOL_O; a--; break;}
						else if(itsX(e, c, l)){e->grelha[c][l] = SOL_X; a--; break;}
						else if(itsOO(e, c, l)){e->grelha[c][l] = SOL_X; a--; break;}
						else if(itsXX(e, c, l)){e->grelha[c][l] = SOL_O; a--; break;}
					}
				} if(!a) break;
			}
		if(!a) e->numAjudas -= 1;
	}
	return *e;
}

/**
Função que resolve o jogo, aplicando ajudas até as ajudas não conseguirem progredir ou o puzzle acabar.
*/
ESTADO solver(ESTADO e){
	ESTADO e1;
	while(valida(e) != 1){
		e1 = e;
		ajudas(&e); e.numAjudas++;
		if( strcmp( estado2str(e1), estado2str(e) ) == 0 ) break;
	}
	return e;
}
