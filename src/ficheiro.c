/**
@file ficheiro.c
Contém as funções relativas à escrita e leitura em ficheiros
*/

#include <stdlib.h>
#include <string.h>
#include "cgi.h"
#include "estado.h"
#include "grelha.h"

#define MAX_BUFFER	  10240

/**
Função que preenche o ficheiro user com o nome do jogador, o tabuleiro selecionado e com as jogadas e ancoras.
*/
void printUserFile(char *utilizador, int tab, int jogada, int ancora) {

	FILE *readfile;
	readfile = fopen("/var/www/html/users/user.txt", "w+");

	fprintf(readfile, "%s\n", utilizador);
	fprintf(readfile, "%d\n", tab);
	fprintf(readfile, "%d\n", jogada);
	fprintf(readfile, "%d\n", ancora);

	fclose(readfile);	
}

/**
Esta função tem como finalidade, dado um numero de uma linha, remover todas as jogadas que se encontram depois dessa dada linha.
Para isso é copiado o conteúdo do ficheiro original para um temporário até à linha dada, e depois é alterado o nome do ficheiro temporario para o nome do ficheiro original, assim substituindo este.
*/
void tiraJogadasFicheiro(char *utilizador, int linha){

	char ficheiroUser[MAX_BUFFER], copyLine[MAX_BUFFER]; 
	snprintf(ficheiroUser, sizeof(ficheiroUser), "/var/www/html/users/%s.txt", utilizador);

	FILE* tempFile = fopen(ficheiroUser, "r+");
    int l = 0;
    FILE* tempFileaux = fopen("/var/www/html/users/tempFile.txt", "a");

	while (fgets(copyLine, sizeof(copyLine), tempFile) && l < linha){
        l++;
        fprintf(tempFileaux, "%s", copyLine);
    }

    fclose(tempFileaux);
    fclose(tempFile);
    rename("/var/www/html/users/tempFile.txt", ficheiroUser);
}

/**
Função que dado o utilizador, o tabuleiro, a jogada e a ancora, escreve esses valores no ficheiro user.txt e invoca a função tiraJogadasFicheiro.
*/
void atualizaUserFile(char *utilizador, int tabuleiro, int jogada, int ancora){

	FILE *readfile;
	readfile = fopen("/var/www/html/users/user.txt", "w+");

	fprintf(readfile, "%s\n", utilizador);
	fprintf(readfile, "%d\n", tabuleiro);
	fprintf(readfile, "%d\n", jogada);
	fprintf(readfile, "%d\n", ancora);

	fclose(readfile);

	tiraJogadasFicheiro(utilizador, jogada);
}

/**
Função que dado os parametros gera o ESTADO
@returns Um novo ESTADO
*/
ESTADO geraESTADO(ESTADO e, int linha, int coluna, FILE *file) {

	int j = 0, i = 0, sizelinha = 0;
	e.num_lins = linha; e.num_cols = coluna; e.numAjudas = 3;
	iniciaVazia(&e);
	sizelinha = coluna-1;
	char stringLinha[sizelinha];

	for (i=0; i<linha; i++){
		fscanf(file, "%s", stringLinha);
		for(j=0; j<coluna; j++){
			if(stringLinha[j]=='#') e.grelha[j][i] = BLOQUEADA;
			else if(stringLinha[j]=='X') e.grelha[j][i] = FIXO_X;
			else if(stringLinha[j]=='O') e.grelha[j][i] = FIXO_O;
			else if(stringLinha[j]=='.') e.grelha[j][i] = VAZIA;
		}
	}

	return e;
}

/**
Função que le o tabuleiro a partir de um ficheiro e retorna o ESTADO gerado
@returns Um novo ESTADO
*/
ESTADO loadFile(char *args) {

	int linha = 0, coluna = 0;
	FILE *file;

	if (strcmp(args, "1") == 0) file = fopen("/var/www/html/facil.txt", "r");
	else if(strcmp(args, "2") == 0) file = fopen("/var/www/html/medio.txt", "r");
	else if(strcmp(args, "3") == 0) file = fopen("/var/www/html/dificil.txt", "r");

	ESTADO e;
	fscanf(file, "%d %d", &linha, &coluna);
	e = geraESTADO(e, linha, coluna, file);

	fclose(file);
	
	return e;
}

/**
Esta função tem como finalidade retornar o valor da ancora mais recente que se encontra no estado da ultima linha do ficheiro que contem as jogadas do utilizador.
@returns Um int com o vavor da ancora mais recente
*/
int getAncora(int jogada, char *utilizador) {

	if(jogada > 1){
		char ficheiro[MAX_BUFFER], lastAncora[MAX_BUFFER]; 
		snprintf(ficheiro, sizeof(ficheiro), "/var/www/html/users/%s.txt", utilizador);

		FILE *userfile; userfile = fopen(ficheiro, "r");

    	int k = 0;	
		while (fgets(lastAncora, sizeof(lastAncora), userfile) && k <= jogada) k++;

    	ESTADO atual = str2estado(lastAncora);
    	int ancora = atual.ancora;
    	return ancora;
	} else return 1;
}

/**
Função que verifica se o utilizador ativo é o mesmo da última vez e se o tabuleiro também é o mesmo.
@returns 1 (para inicializar a variavel pjogada)
*/
int checkUserJogo(char *user, char *userfile, int tab) {

	char user_recente[MAX_BUFFER];
	int tab_recente;

	FILE *checkfile;
	checkfile = fopen("/var/www/html/users/user.txt", "r+");
	fscanf(checkfile, "%s", user_recente);
	fscanf(checkfile, "%d", &tab_recente);
	fclose(checkfile);

	if(strcmp(user_recente, user) != 0 || tab_recente != tab){
		printUserFile(user, tab, 1, 1);
		remove(userfile);

		return 0;
	} else return 1;
}

/**
Função que irá ler os valores do ficheiro user e atualiza-los e de seguida iniciar o jogo.
*/
void preparaUserStart(int pjogada) {
	int tab, jogada, ancora;
	char utilizador[MAX_BUFFER];

	FILE *readfile;
	readfile = fopen("/var/www/html/users/user.txt", "r+");

	fscanf(readfile, "%s", utilizador);
	fscanf(readfile, "%d", &tab);
	fscanf(readfile, "%d", &jogada);
	fscanf(readfile, "%d", &ancora);

	fclose(readfile);

	if(pjogada == 1) jogada++;

	printUserFile(utilizador, tab, jogada, ancora);
	readfile = fopen("/var/www/html/users/user.txt", "r+");

	fscanf(readfile, "%s", utilizador);
	fscanf(readfile, "%d", &tab);
	fscanf(readfile, "%d", &jogada);
	fscanf(readfile, "%d", &ancora);

	fclose(readfile);

	grelha(utilizador, tab, jogada, ancora);
}