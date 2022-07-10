/**
@file extras.c
Contém as funções relativas a elementos extra do jogo
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "ficheiro.h"
#include "verifica.h"

#define MAX_BUFFER	  10240

const char *FICHEIROS[] = {"bloqueada.png", "cruzAZUL.png", "circuloAZUL.png", "vazia.png", "cruzAZUL.png", "circuloAZUL.png"};

/**
Esta função imprime no ecrã a mensagem de vitória ou de derrota e elimina o ficheiro do utilizador dado o utilizador, o tabuleiro e o inteiro que representa o resultado, quando o jogo termina.
**/
void mensagemFinal(char *utilizador, int tabuleiro, int jogada, int result){

	char buf[MAX_BUFFER]; 
	int score = (tabuleiro*500)/jogada * result;
	snprintf(buf, sizeof(buf), "/var/www/html/users/%s.txt", utilizador);

	COMECAR_HTML;

	if(result == 1) printf("<div class='mensagem'><h1>Vitória</h1><p>Pontuação: %d</p></div>", score);
	else printf("<div class='mensagem'><h1>Perdeu</h1><p>Pontuação: %d</p></div>", score);

	ABRIR_DIV_BUTTONS;
	BOTAO_LINK_medio("http://localhost/cgi-bin/GandaGalo", "Novo Jogo");
	DIV_CLEAR;
	FECHAR_DIV;
	FECHAR_HTML;
	
	atualizaUserFile("user", tabuleiro, 1, 1);
}

/**
Função que dada a QUERY_STR verifica se esta está vazia
@returns 1 caso a QUERY_STR não esteja vazia e 0 se estiver vazia
*/
int processaQuery (char *args){
	if(args == NULL || strlen(args) == 0) return 0;
	else return 1;
}

/**
Lê o valor fornecido e segundo as regras do jogo retorna o valor corresponde à ação de clicar.
@returns O VALOR
*/
VALOR atualiza(VALOR v){

	switch(v){
		case VAZIA:
			return SOL_X;
		case SOL_X:
			return SOL_O;
		case SOL_O:
			return VAZIA;
		default:
			return v;
	}
}

/**
Esta função tem como finalidade, dado um numero de coluna e linha e um estado, criar o link atualizado.
*/
void criaLink (int l, int c, ESTADO e){

	ESTADO e2 = e;
	e2.grelha [l][c] = atualiza(e2.grelha[l][c]);
	
	char *s = estado2str(e2);
	char buffer[MAX_BUFFER];

	sprintf(buffer, "GandaGalo?%s", s);

	ABRIR_LINK(buffer);
}

/** 
Função que escreve os botões menu, voltar e ajuda no ecrã.
*/
void botoesMenuVoltarAjuda(int jogada, ESTADO e, char *userfile){

	int i = 0;
	char lastLine[MAX_BUFFER], linkVoltar[MAX_BUFFER], ajuda[MAX_BUFFER];

	FILE* voltarFile = fopen(userfile, "r+");
    while (fgets(lastLine, sizeof(lastLine), voltarFile) && i <= jogada) i++;
    fclose(voltarFile);

    if(jogada == 1) sprintf(linkVoltar, "GandaGalo");
    else sprintf(linkVoltar, "GandaGalo?v%s", lastLine);

	sprintf(ajuda, "GandaGalo?%s", estado2str(ajudas(&e)));

	BOTAO_LINK_normal("http://localhost/cgi-bin/GandaGalo", "Menu");
	BOTAO_LINK_normal(linkVoltar, "Voltar");
	BOTAO_LINK_normal(ajuda, "Ajuda");
}

/** 
Função que escreve os botões colocar e regressar ancora no ecrã.
*/
void botoesColocarRegressarAncora(char *link, int jogada, int valorAncora, char *setAncora, char *regressaDeAncora, char *userfile){

    int f = 0;
    char ancoraLine[MAX_BUFFER], linkVoltaAncora[MAX_BUFFER], linkSetAncora[MAX_BUFFER];

	FILE* ancoraFile = fopen(userfile, "r+");
    while (fgets(ancoraLine, sizeof(ancoraLine), ancoraFile) && f < (valorAncora-1)) f++;
    fclose(ancoraFile);

    if(valorAncora == 1) sprintf(linkVoltaAncora, "GandaGalo");
    else sprintf(linkVoltaAncora, "GandaGalo?r%s", ancoraLine);

    if(jogada == 1) sprintf(linkSetAncora, "GandaGalo");
    else if(strcmp(setAncora, link) == 0) sprintf(linkSetAncora, "GandaGalo?%s", link);
    else if(strcmp(regressaDeAncora, link) == 0) sprintf(linkSetAncora, "GandaGalo?a%s", &link[1]);
    else sprintf(linkSetAncora, "GandaGalo?a%s", link);

    BOTAO_LINK_grande(linkSetAncora, "Colocar Âncora");
	BOTAO_LINK_grande(linkVoltaAncora, "Regressar Âncora");
}

/** 
Função que escreve os botões do jogo com os respetivos links no ecrã.
*/
void botoesJogo(char *link, int jogada, int valorAncora, ESTADO e, char *setAncora, char *regressaDeAncora, char *userfile){	
	ABRIR_DIV_BUTTONS;
	botoesMenuVoltarAjuda(jogada, e, userfile);
	botoesColocarRegressarAncora(link, jogada, valorAncora, setAncora, regressaDeAncora, userfile);
	DIV_CLEAR;
	FECHAR_DIV;
}

/** 
Função que escreve os elementos do jogo com os respetivos links no ecrã.
*/
void printGame(char *link, int tabuleiro, int jogada, int valorAncora, ESTADO e, char *setAncora, char *regressaDeAncora, char *userfile){
	COMECAR_HTML;

	if(tabuleiro == 1) ABRIR_SVG(180, 180);
	else if(tabuleiro == 2) ABRIR_SVG(250, 250);
 	else if(tabuleiro == 3) ABRIR_SVG(320, 320);
	
	for (int c = 0; c < e.num_cols; ++c){
		for (int l = 0; l < e.num_lins; ++l){
			criaLink(c, l, e);
			IMAGEM(c, l, 40, FICHEIROS[(VALOR) e.grelha[c][l]]);
			FECHAR_LINK;
		}
	}
	
	FECHAR_SVG;
	botoesJogo(link, jogada, valorAncora, e, setAncora, regressaDeAncora, userfile);
	FECHAR_HTML;
}

/** 
Função que escreve os botões com os respetivos links para iniciar o jogo.
*/
int menu(){

	COMECAR_HTML;
	LOGO;
	BOTAO_JOGO("1", "Fácil");
	BOTAO_JOGO("2", "Médio");
	BOTAO_JOGO("3", "Difícil");
	BOTAO_JOGO("4", "Gerar");
	FECHAR_HTML;

	return 0;
}